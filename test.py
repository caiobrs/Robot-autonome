#!/usr/bin/env python
# coding: utf-8

# In[34]:


import enum
from mesa import Agent
from mesa import Model
from mesa.space import MultiGrid
from mesa.time import RandomActivation
import numpy
from mesa.datacollection import DataCollector
import pandas
from bokeh.io import output_notebook, push_notebook
from bokeh.models import ColumnDataSource, Line, Legend, HoverTool, LinearColorMapper
from bokeh.palettes import Category10
from bokeh.plotting import figure, show

#Classe qui représente l'état d'un agent
class State(enum.IntEnum):
    SUSCEPTIBLE = 0
    INFECTED = 1
    REMOVED = 2
    DEAD = 3

class MyAgent(Agent):
    """ An agent in an epidemic model."""
    def __init__(self, unique_id, model):
        super().__init__(unique_id, model)
        #valeur issue d'une distribution gaussienne de moyenne 40 et écart-type 20
        self.age = self.random.normalvariate(40,20)        
        self.state = State.SUSCEPTIBLE
        #variable qui contient l'heure d'infection
        self.infection_time = 0
    
    def move(self):
        """Move the agent"""
        #selectionner les 8 cases autour de la position initiale de l'agent (la position initiale exclue)
        #si moore=False (que les 4 cases : top/down/left/right)
        possible_steps = self.model.grid.get_neighborhood(self.pos,moore=True,include_center=False)
        new_position = self.random.choice(possible_steps)
        #faire bouger l'agent vers cette nouvelle position
        self.model.grid.move_agent(self, new_position)
    
    def status(self):
        """Check infection status"""

        if self.state == State.INFECTED:
            #la probabilité de mortalité d'un agent est fixe (celle du modèle)
            drate = self.model.death_rate
            #determiner si la personne est décédée
            #l'individu est décédé avec une probabilité de drate (initialisée à 0.02)
            #l'individu reste en vie avec une probabilité de (1-drate)
            alive = numpy.random.choice([0,1], p=[drate,1-drate])
            if alive == 0:
                self.state = State.DEAD
                #print("I am dead n°"+str(self.unique_id))
            #print("I am not dead n°"+str(self.unique_id))
            t = self.model.schedule.time-self.infection_time
           
            #si le temps nécessaire est écoulé, l'agent n'est plus malade
            if t >= self.recovery_time:          
                self.state = State.REMOVED
    
            
    
    
    def contact(self):
        """Find close contacts and infect"""

        #determiner le nombre total d'agents dans la même position que notre agent
        cellmates = self.model.grid.get_cell_list_contents([self.pos])       
        if len(cellmates) > 1: #càd que l'agent n'est pas seul dans la cellule
            for other in cellmates:
                if self.random.random() > model.ptrans:
                    continue
                if self.state is State.INFECTED and other.state is State.SUSCEPTIBLE:                    
                    other.state = State.INFECTED
                    other.infection_time = self.model.schedule.time
                    other.recovery_time = model.get_recovery_time()
    
    #la fonction principale de l'agent (son comportement)
    def step(self):
        self.status()
        self.move()
        self.contact()



def get_column_data(model):
    agent_state = model.datacollector.get_agent_vars_dataframe()
    X = pandas.pivot_table(agent_state.reset_index(),index='Step',columns='State',aggfunc=numpy.size,fill_value=0)    
    labels = ['Susceptible','Infected','Removed','Dead']
    X.columns = labels[:len(X.columns)]
    return X      
    
        
#la classe SMA
class InfectionModel(Model):
    """A model for infection spread."""

    def __init__(self, N=10, width=10, height=10, ptrans=0.5,
                 death_rate=0.02, recovery_days=21,
                 recovery_sd=7):

        self.num_agents = N
        self.recovery_days = recovery_days
        self.recovery_sd = recovery_sd
        self.ptrans = ptrans
        self.death_rate = death_rate
        self.deaths = 0
        self.grid = MultiGrid(width, height, True)
        
        #l'ordonnanceur du modele (instance de RandomActivation)
        #tester SimultaneousActivation (qui permet d'activer tous les agents en mêê temps)
        self.schedule = RandomActivation(self)
        self.running = True
        self.dead_agents = []
        # Create agents
        for i in range(self.num_agents):
            a = MyAgent(i, self)
            self.schedule.add(a)
            # Add the agent to a random grid cell
            x = self.random.randrange(self.grid.width)
            y = self.random.randrange(self.grid.height)
            self.grid.place_agent(a, (x, y))
            #make some agents infected at start
            # parametrer la proba d'infection (pour l'etat initial du systeme)
            infected = numpy.random.choice([0,1], p=[0.25,0.75])
            if infected == 1:
                a.state = State.INFECTED
                a.recovery_time = self.get_recovery_time()

        self.datacollector = DataCollector(          
            agent_reporters={"State": lambda a: a.state})

    def get_recovery_time(self):
        #retourne une durée de retablissement de moyenne (self.recovery_days) et d'ecart type (self.recovery_sd)
        return int(self.random.normalvariate(self.recovery_days,self.recovery_sd))

    def step(self):
        #le modèle récupere les données de simulation par étape
        self.datacollector.collect(self)
        #passage de l'instant t à l'instant (t+1)
        self.schedule.step()


def grid_values(model):
        """Get grid cell states"""
        agent_counts = numpy.zeros((model.grid.width, model.grid.height))
        w=model.grid.width
        df=pandas.DataFrame(agent_counts)
        for cell in model.grid.coord_iter():
            agents, x, y = cell
            c=None
            for a in agents:
                 c = a.state
            df.iloc[x,y] = c
        return df    
        
#revoir les coleurs des cellules selon l'état des agents         
def plot_cells_bokeh(model):
    agent_counts = numpy.zeros((model.grid.width, model.grid.height))
    w=model.grid.width
    df=grid_values(model)
    df = pandas.DataFrame(df.stack(), columns=['value']).reset_index()
    columns = ['value']
    x = [(i, "@%s" %i) for i in columns]
    hover = HoverTool(
      tooltips=x, point_policy='follow_mouse')
    colors = Category10[4]
    mapper = LinearColorMapper(palette=colors, low=df.value.min(), high=df.value.max())
    p = figure(plot_width=500,plot_height=500, tools=[hover], x_range=(-1,w), y_range=(-1,w))
    p.rect(x="level_0", y="level_1", width=1, height=1,
      source=df,
      fill_color={'field':'value', 'transform': mapper},
      line_color='black')
    p.background_fill_color = "black"
    p.grid.grid_line_color = None
    p.axis.axis_line_color = None
    p.toolbar.logo = None
    return p

def plot_states_bokeh(model,title=''):
    """Plot cases per country"""
#récupération des données de simulation
    X = get_column_data(model)
    X = X.reset_index()
    
    source = ColumnDataSource(X)
    i=0
    colors = Category10[4]
    items=[]
    p = figure(plot_width=600,plot_height=400,tools=[],title=title,x_range=(0,100))        
    for c in X.columns[1:]:
        line = Line(x='Step',y=c, line_color=colors[i],line_width=4,line_alpha=.8,name=c)
        glyph = p.add_glyph(source, line)
        i+=1
        items.append((c,[glyph]))

    p.xaxis.axis_label = 'Step'
    p.add_layout(Legend(location='center_right',   
                items=items))
    p.background_fill_color = "#e1e1ea"
    p.background_fill_alpha = 0.5
    p.legend.label_text_font_size = "10pt"
    p.title.text_font_size = "15pt"
    p.toolbar.logo = None
    p.sizing_mode = 'scale_height'    
    return p       

steps=50 
pop=100
output_notebook()

#usar parametros de transmissao antes e apos vacina
#taxa de mortalidade no começo da pandemia e agora com a variante
#comparar gráficos

model = InfectionModel(pop, 5, 5, ptrans=0.5, death_rate=0.01)


for i in range(steps):
    model.step()
    p1=plot_states_bokeh(model,title='step=%s' %(i+1))
    handle=show(p1, notebook_handle=True)
    p2=plot_cells_bokeh(model)
    handle=show(p2, notebook_handle=True)
    #push_notebook()
   

#print(model.datacollector.get_agent_vars_dataframe())
#print(get_column_data(model))


# In[ ]: