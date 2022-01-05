var stageMap = 0;

$(".mapFirstStage .btnMapFirst").click(function() {
    $("#btnChooseImage").click();
});

$("#btnChooseImage").change(function(event) {
    $(".mapFirstStage .imgMap").attr("src", URL.createObjectURL(event.target.files[0]));

    $(".mapFirstStage .mapButtons").css("top", "calc(50% - 60px)");
    $(".mapFirstStage .btnMapFirst").val("Choose other image");
    $(".mapFirstStage .btnMapConfirm").css("display", "inline");

    setTimeout(function(){
        $(".mapFirstStage .imgMap").css("top", "calc(50% - " + ($(".mapFirstStage .imgMap").innerHeight() / 2) + "px)");
    }, 40);

});