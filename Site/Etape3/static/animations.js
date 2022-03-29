var stageMap = 1;
var stateAnimation = 0; //free to animate

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

        $("#mainProgessText").html("3. At this point you will possess 2 of the 4 stationary beacons, "+ 
            "the other 2 will be shown according to their current position.");

        var btnSetFirstBeacon = $("#mainOptionExample").clone();
        btnSetFirstBeacon.attr("id", "btnSetFirstBeacon");
        btnSetFirstBeacon.val("Set First Beacon");
        btnSetFirstBeacon.appendTo(".mainController .mainOptions");
        btnSetFirstBeacon.click(btnSetFirstBeacon_Click);

        var btnSetSecondBeacon = $("#mainOptionExample").clone();
        btnSetSecondBeacon.attr("id", "btnSetSecondBeacon");
        btnSetSecondBeacon.val("Set Second Beacon");
        btnSetSecondBeacon.appendTo(".mainController .mainOptions");
        btnSetSecondBeacon.click(btnSetSecondBeacon_Click);

        $("#mainProgessText").fadeIn("slow", function() {
            btnSetFirstBeacon.fadeIn("slow", function() {
                btnSetSecondBeacon.fadeIn("slow");
            });
        });

        $("#mainProgressThree").animate({
            backgroundColor: "purple"
        });
    });
}

//---------------------------------------------------------------------------------\\
//-----------------------------------Third Step------------------------------------\\
//---------------------------------------------------------------------------------\\

var movingBeacon = 0;

function btnSetFirstBeacon_Click() {
    var btnBeacon = $("#btnSetFirstBeacon");

    if (btnBeacon.val() == "Set First Beacon") {
        if (stateAnimation == 0) {
            btnBeacon.val("Cancel");
            stateAnimation = 1;
            movingBeacon = 1;
            $("#mapBeaconControl").css("display", "inline");

            $("#elemBeacon1").remove();
            var elemBeacon = $("#beaconExample").clone();
            elemBeacon.attr("id", "elemBeacon1");
            elemBeacon.appendTo(".mapBody .imgMap");
            elemBeacon.fadeIn("slow");

            $("#elemBeacon1 p").html("" + nBeacons[0]);
        }
    }
    else {
        btnBeacon.val("Set First Beacon");
        stateAnimation = 0;
        movingBeacon = 0;
        $("#mapBeaconControl").css("display", "none");
    }

}

function btnSetSecondBeacon_Click() {
    var btnBeacon = $("#btnSetSecondBeacon");

    if (btnBeacon.val() == "Set Second Beacon") {
        if (stateAnimation == 0) {
            btnBeacon.val("Cancel");
            $("#mapBeaconControl").css("display", "inline");
            stateAnimation = 1;
            movingBeacon = 2;

            $("#elemBeacon2").remove();
            var elemBeacon = $("#beaconExample").clone();
            elemBeacon.attr("id", "elemBeacon2");
            elemBeacon.appendTo(".mapBody .imgMap");
            elemBeacon.fadeIn("slow");
            
            $("#elemBeacon2 p").html("" + nBeacons[1]);
        }
    }
    else {
        btnBeacon.val("Set Second Beacon");
        $("#mapBeaconControl").css("display", "none");
        stateAnimation = 0;
        movingBeacon = 0;
    }
}

$("#mapBeaconControl").mousemove(function(e) {
    var elemBeaconToMove = $("#elemBeacon" + movingBeacon);
    
    elemBeaconToMove.css("left", (e.pageX - $(".mapBody .imgMap").offset().left) * 100 / $(".mapBody .imgMap").width()  + "%");
    elemBeaconToMove.css("top", (e.pageY - $(".mapBody .imgMap").offset().top) * 100 / $(".mapBody .imgMap").height()  + "%");
});

$("#mapBeaconControl").mousedown(function(e) {
    console.log(movingBeacon);
    if (movingBeacon == 1)
        $("#btnSetFirstBeacon").val("Set First Beacon");
    else if (movingBeacon == 2) 
        $("#btnSetSecondBeacon").val("Set Second Beacon");
     
    
    $("#mapBeaconControl").css("display", "none");
    stateAnimation = 0;
    movingBeacon = 0;
});

//---------------------------------------------------------------------------------\\
//----------------------------------Zoom Control-----------------------------------\\
//---------------------------------------------------------------------------------\\

$("#btnMapZoomControl").click(function() {
    if ($("#btnMapZoomControl").val() == "Move Map") {
        if (stateAnimation == 0) {
            stateAnimation = 1;
            $("#btnMapZoomControl").val("Controlling Map...");
            $("#mapZommControl").css("display", "inline");
        }
    }
    else {
        stateAnimation = 0;
        $("#btnMapZoomControl").val("Move Map");
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