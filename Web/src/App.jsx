import React from 'react';
import { FaLightbulb} from 'react-icons/fa';
import { FaTemperatureLow} from 'react-icons/fa';
import { WiHumidity} from 'react-icons/wi';

import CanvasJSReact from './assets/scripts/canvasjs.react';
var CanvasJSChart = CanvasJSReact.CanvasJSChart;

const API_URL = "http://192.168.0.15/api";
const TEMPERATURE_LOGS_NAME = "dataPointsTemp";
const HUMIDITY_LOGS_NAME = "dataPointsHumd";
const DIGITAL_LIGHT_PIN = 7;
const VIRTUAL_TEMPERATURE_PIN= 150;
const VIRTUAL_HUMIDITY_PIN= 151;
const GET_WETHER_VALUES_INTERVAL = 60000;

const tempData = [{"label":"23:10","y":29.2,"x":0},{"label":"23:10","y":29.2,"x":1},{"label":"23:10","y":28.9,"x":2},{"label":"23:10","y":28.5,"x":3},{"label":"23:10","y":28.2,"x":4},{"label":"23:10","y":27.9,"x":5},{"label":"23:11","y":27.7,"x":6},{"label":"23:11","y":27.5,"x":7},{"label":"23:11","y":27.5,"x":8},{"label":"23:11","y":27.2,"x":9},{"label":"23:11","y":26.9,"x":10},{"label":"23:12","y":26.5,"x":11},{"label":"23:12","y":26.8,"x":12},{"label":"23:12","y":26.9,"x":13},{"label":"23:12","y":26.2,"x":14}]
const humidData = [{"label":"15:10","y":87,"x":0},{"label":"15:25","y":87,"x":1},{"label":"15:32","y":87,"x":2},{"label":"15:43","y":85,"x":3},{"label":"15:52","y":84,"x":4},{"label":"16:11","y":86,"x":5},{"label":"16:20","y":86,"x":6},{"label":"16:35","y":86,"x":7},{"label":"16:42","y":88,"x":8},{"label":"16:51","y":88,"x":9},{"label":"17:01","y":89,"x":10},{"label":"17:12","y":85,"x":11},{"label":"17:23","y":84,"x":12},{"label":"17:30","y":85,"x":13},{"label":"17:45","y":86,"x":14},{"label":"17:56","y":87}]

export default class App extends React.Component {
    getTemperatureInterval = undefined;
    getHumidityInterval = undefined;

    state = {
        lamp: false,
        temperature: 0,
        humidity: 0,
        temperatureList: [],
        humidityList: [], 
    }

    componentDidMount(){
        // localStorage.setItem(TEMPERATURE_LOGS_NAME, JSON.stringify(tempData));
        // localStorage.setItem(HUMIDITY_LOGS_NAME, JSON.stringify(humidData));

        var datapoints = JSON.parse(localStorage.getItem(TEMPERATURE_LOGS_NAME));
        if(datapoints != null && datapoints.length > 0){
            this.setState({temperatureList: datapoints, temperature: datapoints[datapoints.length - 1].y});
            datapoints = null;
        }
        
        datapoints = JSON.parse(localStorage.getItem(HUMIDITY_LOGS_NAME));
        if(datapoints != null && datapoints.length > 0){
            this.setState({humidityList: datapoints, humidity: datapoints[datapoints.length - 1].y});
        }

        this.setDefaultConfiguration();
        this.getTemperatureInterval = setInterval(() => this.getTemperature(), GET_WETHER_VALUES_INTERVAL);
        this.getHumidityInterval = setInterval(() => this.getHumidity(), GET_WETHER_VALUES_INTERVAL + 3000);
    }
    
    componentWillUnmount(){
        clearInterval(this.getTemperatureInterval);
        clearInterval(this.getHumidityInterval);
    }

    setDefaultConfiguration(){
        fetch(`${API_URL}/setpintype?pin=${DIGITAL_LIGHT_PIN}&type=output`).then(x=> x.json()).then(x=> {
            if(!x.success) alert("Erro na configuração da lâmpada.");
        });
        fetch(`${API_URL}/setdigitalpin?pin=${DIGITAL_LIGHT_PIN}&value=1`).then(x=> x.json())
            .then(()=> this.setState({lamp: !this.state.lamp}));
    }

    setLamp(){
        fetch(`${API_URL}/setdigitalpin?pin=${DIGITAL_LIGHT_PIN}&value=${!this.state.lamp ? 0 : 1}`).then(x=> x.json())
            .then(()=> this.setState({lamp: !this.state.lamp}));
    }

    getTemperature(){
        fetch(`${API_URL}/getvirtualpin?pin=${VIRTUAL_TEMPERATURE_PIN}`).then(x=> x.json()).then(x=> {
            if(!x.success || !x.pin.value)
                return;

            var date = new Date();
            var object = {
                label: `${date.getHours() > 9 ? date.getHours() : "0" + date.getHours()}:${date.getMinutes() > 9 ? date.getMinutes() : "0" + date.getMinutes()}`,
                y: x.pin.value
            };
            
            var aux = this.state.temperatureList;
            aux.push(object);
            localStorage.setItem(TEMPERATURE_LOGS_NAME, JSON.stringify(aux));
            this.setState({temperature: x.pin.value, temperatureList: aux});
        });
    }

    getHumidity(){
        fetch(`${API_URL}/getvirtualpin?pin=${VIRTUAL_HUMIDITY_PIN}`).then(x=> x.json()).then(x=> {
            if(!x.success || !x.pin.value)
                return;

            var date = new Date();
            var object = {
                label: `${date.getHours() > 9 ? date.getHours() : "0" + date.getHours()}:${date.getMinutes() > 9 ? date.getMinutes() : "0" + date.getMinutes()}`,
                y: x.pin.value
            };
            
            var aux = this.state.humidityList;
            aux.push(object);
            localStorage.setItem(HUMIDITY_LOGS_NAME, JSON.stringify(aux));
            this.setState({humidity: x.pin.value, humidityList: aux});
        });
    }

    render(){
        const tempOptions = {
			animationEnabled: true,
			title: {
                text: `${this.state.temperature} °C`
            },
			theme: "dark1",   
            backgroundColor: "#303030",  
            markerSize: 5,
			data: [{
				color: "#b7556c",
                type: "splineArea",
				dataPoints: this.state.temperatureList
			}]
		}

        const humdOptions = {
			animationEnabled: true,
			title: {
                text: `${this.state.humidity} %`
            },
			theme: "dark1",   
            backgroundColor: "#303030",  
            markerSize: 5,
			data: [{
				color: "#384b91",
                type: "splineArea",
				dataPoints: this.state.humidityList
			}]
		}
        
        return (
            <>
                <nav className="navbar navbar-expand-lg navbar-dark bg-dark" style={{marginBottom: "30px"}}>
                    <a className="navbar-brand" href="#">Automação - Arduino</a>
                    <button className="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
                        <span className="navbar-toggler-icon"></span>
                    </button>
                </nav>

                <div className="container">
                    <div className="row">
                        <div className="col-12">
                            <div className="bs-component">
                                <div className="row">
                                    <div className="col-12">
                                        <div className="alert alert-dark d-flex align-items-center" style={{cursor: "pointer"}} role="alert" onClick={()=> this.setLamp()}>
                                            <FaLightbulb fill={this.state.lamp ? "#f39c12" : "#5f5f5f"} style={{width:"20px", height:"50px"}}/> 
                                            <div style={{fontSize: "20px", paddingLeft: "15px", paddingTop: "10px", paddingBottom:"10px"}}>{this.state.lamp ? "Desligar" : "Acender"} luz</div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-12 mt-3">
                            <div className="bs-component">
                                <div className="row">
                                    <div className="col-12">
                                        <div className="alert alert-dark d-flex align-items-center" role="alert">
                                            <FaTemperatureLow fill="#b7556c" style={{width:"28px", height:"50px"}}/> 
                                            <div style={{fontSize: "20px", paddingLeft: "15px", paddingTop: "10px", paddingBottom:"10px"}}>Temperatura: {this.state.temperature}°C</div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-12 mt-3">
                            <div className="bs-component">
                                <div className="row">
                                    <div className="col-12">
                                        <div className="alert alert-dark d-flex align-items-center" role="alert" style={{paddingLeft: "10px"}}>
                                            <WiHumidity fill="#384b91" style={{width:"37px", height:"50px"}}/> 
                                            <div style={{fontSize: "20px", paddingLeft: "15px", paddingTop: "10px", paddingBottom:"10px"}}>Humidade: {this.state.humidity}%</div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-md-12 mt-3">
                            <div className="bs-component">
                                <div className="row">
                                    <div className="col-12">
                                        <div className="card mb-3">
                                            {/* <div className="card-header">
                                                <h4 className="card-title">Temperatura</h4>
                                            </div> */}
                                            <div className="card-content">
                                                <div className="card-body">
                                                    <div className="text-center">
                                                        <CanvasJSChart options = {tempOptions} style={{ height: "300px", width: "100%" }} onRef={ref => this.tempChart = ref} />
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-md-12 mt-3">
                            <div className="bs-component">
                                <div className="row">
                                    <div className="col-12">
                                        <div className="card mb-3">
                                            {/* <div className="card-header">
                                                <h4 className="card-title">Humidade</h4>
                                            </div> */}
                                            <div className="card-content">
                                                <div className="card-body">
                                                    <div className="text-center">
                                                        <CanvasJSChart options = {humdOptions} style={{ height: "300px", width: "100%" }} onRef={ref => this.humidChart = ref} />
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </>
        );
    }
}