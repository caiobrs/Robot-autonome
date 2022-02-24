var stageMap = 1;


//---------------------------------------------------------------------------------\\
//----------------------------------First Step-------------------------------------\\
//---------------------------------------------------------------------------------\\

$(".mapFirstStage .btnMapFirst").click(function() {
    $("#btnChooseImage").click();
});

$("#btnChooseImage").change(function(event) {
    $(".mapBody .imgMap .imgMapBackImage").attr("src", URL.createObjectURL(event.target.files[0]));

    $(".mapBody .mapButtons").css("top", "calc(50% - 60px)");
    $(".mapBody .btnMapFirst").val("Choose other image");
    $(".mapBody .btnMapConfirm").css("display", "inline");

    setTimeout(function(){
        $(".mapBody .imgMap").css("top", "calc(50% - " + ($(".mapBody .imgMap").innerHeight() / 2) + "px)");
    }, 40);
});

$(".mapFirstStage .btnMapConfirm").click(function() {
    stageMap++;
    $(".mapFirstStage").fadeOut("slow");

    $("#mainLineProgressBar").effect( "size", {
        to: { width: $("#mainLineProgressBar").parent().width() * 0.20 }
      }, 1000 );

    $("#mainProgessText").fadeOut("slow", function() {

        var btnConfirm = $("#mainOptionExample").clone();
        btnConfirm.attr("id", "btnConfirmStepTwo");
        btnConfirm.val("Confirm");
        btnConfirm.appendTo(".mainController .mainOptions");
        btnConfirm.click(btnConfirm_Click);

        $("#mainProgessText").fadeIn("slow", function() {
            btnConfirm.fadeIn("slow");
        });

        $("#btnMapZoomControl").fadeIn("slow");

        $("#mainProgessText").html("2. At this point you should adjust the map on the side so that it " +
                "looks the way you want it. You should adjust the ZOOM and move the image as you like.<br>" +
                "To do this, you click on the \"Position Map\" button");
        $("#mainProgressTwo").animate({
            backgroundColor: "purple"
          });
    });
});

//---------------------------------------------------------------------------------\\
//----------------------------------Second Step------------------------------------\\
//---------------------------------------------------------------------------------\\

function btnConfirm_Click() {
    $("#btnConfirmStepTwo").fadeOut("slow", function() {
        $("#btnConfirmStepTwo").remove();
    })

    $("#mainLineProgressBar").effect( "size", {
        to: { width: $("#mainLineProgressBar").parent().width() * 0.40 }
      }, 1000 );
    
    $("#mainProgessText").fadeOut("slow", function() {

        $("#btnMapZoomControl").fadeIn("slow");

        $("#mainProgessText").html("3. Vamo ver ainda o q vai ser escrito");

        $("#mainProgessText").fadeIn();

        $("#mainProgressThree").animate({
            backgroundColor: "purple"
        });
    });
}

//---------------------------------------------------------------------------------\\
//----------------------------------Zoom Control-----------------------------------\\
//---------------------------------------------------------------------------------\\

$("#btnMapZoomControl").click(function() {
    if ($("#btnMapZoomControl").val() == "Position Map") {
        $("#btnMapZoomControl").val("Controlling Zoom...");
        $("#mapZommControl").css("display", "inline");
    }
    else {
        $("#btnMapZoomControl").val("Position Map");
        $("#mapZommControl").css("display", "none");
    }
});

var statusMouseDownStepTwo = false;
var positionInitialX;
var positionInitialY;

$("#mapZommControl").mousedown(function(e) {
    positionInitialX = e.pageX;
    positionInitialY = e.pageY;
    statusMouseDownStepTwo = true;
    $("#mapZommControl").css("cursor", "none");
})

$("#mapZommControl").mouseup(function() {
    statusMouseDownStepTwo = false;
    $("#mapZommControl").css("cursor", "pointer");
})

$("#mapZommControl").mousemove(function(e) {
    if (statusMouseDownStepTwo) {
        $(".mapDefault .imgMap").css("left", "+=" + (e.pageX - positionInitialX) + "px");
        $(".mapDefault .imgMap").css("top", "+=" + (e.pageY - positionInitialY) + "px");
        positionInitialX = e.pageX;
        positionInitialY = e.pageY;
    }
});

$('#mapZommControl').bind('mousewheel', function(e){
    var widthImage = $(".mapDefault .imgMap").width();
    var heightImage = $(".mapDefault .imgMap").height();
    var positionRelativeMouseX = (e.pageX - $('#mapZommControl').offset().left - $(".mapDefault .imgMap").position().left) / $('.mapDefault .imgMap').width() * 0.1;
    var positionRelativeMouseY = (e.pageY - $('#mapZommControl').offset().top - $(".mapDefault .imgMap").position().top) / $('.mapDefault .imgMap').height() * 0.1;

    if (e.originalEvent.wheelDelta > 0) {
        $(".mapDefault .imgMap").css("width", "+=" + widthImage * 0.1 + "px");
        $(".mapDefault .imgMap").css("left", "-=" + widthImage * positionRelativeMouseX + "px");
        $(".mapDefault .imgMap").css("top", "-=" + heightImage * positionRelativeMouseY + "px");
    }
    else {
        $(".mapDefault .imgMap").css("width", "-=" + widthImage * 0.1 + "px");
        $(".mapDefault .imgMap").css("left", "+=" + widthImage * positionRelativeMouseX + "px");
        $(".mapDefault .imgMap").css("top", "+=" + heightImage * positionRelativeMouseY + "px");
    }
});