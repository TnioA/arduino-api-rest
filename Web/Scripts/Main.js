// obter temperatura de 15 em 15 segundos
var timerTemp = setInterval(ObterTemperatura, 15000);

var chart = new CanvasJS.Chart("chartContainer", { 
    title: {
        text: "0°C"
    },
    theme: "dark1",
    data: [
    {
        type: "splineArea",
        dataPoints: [	
        ]
    }
    ]
});
chart.render();	


$(function() {
    $("#valor-luz").knob({
        "release" : function (v) { AtualizaLed2(v);},
        "min":0,
        "max":255,
        "skin":"tron",
        "inputColor": "#00bc8c",
        "fgColor":"#00bc8c",
    });

    $("#valor-temperatura").knob({
        "min":0,
        "max":100,
        "skin":"tron",
        "inputColor": "#00bc8c",
        "fgColor":"#00bc8c",
    });
});


$.ajax({
    method: "POST",
    url: "http://192.168.100.250/",
    success: function(result){
        console.log(result);
    },
    error: function(err){
        console.log(err);
    }
});

function AtualizaLed(){
    var valor = $("#slider_led").val();
    console.log(valor);
    $.ajax({
        method: "POST",
        url: `http://192.168.100.250/api/setpin/9/${valor}`,
        success: function(result){
            $("#valor-luz-alterado").html(valor);
            $('#valor-luz').val(valor).trigger('change');
        },
        error: function(err){
            console.log(err);
        }
    });
}
function AtualizaLed2(valor){
    $.ajax({
        method: "POST",
        url: `http://192.168.100.250/api/setpin/9/${valor}`,
        success: function(result){
            $("#valor-luz-alterado").html(valor);
            $("#slider_led").val(valor)
            $('#valor-luz').val(valor).trigger('change');
            
        },
        error: function(err){
            console.log(err);
        }
    });
}

function ObterLuzLed(){
    $.ajax({
        method: "POST",
        url: "http://192.168.100.250/",
        success: function(result){
            $("#slider_led").val(result.response["light-level"]);
            $("#valor-luz-alterado").html(result.response["light-level"]);
            $('#valor-luz').val(result.response["light-level"]).trigger('change');
        },
        error: function(err){
            console.log(err);
        }
    });
}

function ObterTemperatura(){
    var time = new Date();
    $.ajax({
        method: "POST",
        url: "http://192.168.100.250/",
        success: function(result){

            $('#valor-temperatura').val(result.response["temperature"] + "°").trigger("change");
            chart.options.title.text = result.response["temperature"] + "°";
            chart.options.data[0].dataPoints.push({label: time.getHours() + ":" + time.getMinutes() , y: result.response["temperature"]});
            chart.render();
        },
        error: function(err){
            console.log(err);
        }
    });
}
ObterLuzLed();
ObterTemperatura();