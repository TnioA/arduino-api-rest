import React from 'react';
import { FaLightbulb} from 'react-icons/fa';
import { FaTemperatureLow} from 'react-icons/fa';
import { WiHumidity} from 'react-icons/wi';

import CanvasJSReact from './assets/scripts/canvasjs.react';
var CanvasJSChart = CanvasJSReact.CanvasJSChart;

export default class App extends React.Component {

    getDataInterval = undefined;

    state = {
        lamp: false,
        temperature: 0,
        humidity: 0,
        temperatureList: [],
        humidityList: [], 
    }

    componentDidMount() {
        this.getDataInterval = setInterval(() => {
            this.getTemperature();
            this.getHumidity();
            }, 60000);
        }
    
    componentWillUnmount(){
        clearInterval(this.getDataInterval);
    }

    setLamp(){
        this.setState({lamp: !this.state.lamp});
    }

    getTemperature(){
        var min = Math.ceil(40);
        var max = Math.floor(25);
        var value = Math.floor(Math.random() * (max - min)) + min;

        var date = new Date();
        var object = {
            label: `${date.getHours() > 9 ? date.getHours() : "0" + date.getHours()}:${date.getMinutes() > 9 ? date.getMinutes() : "0" + date.getMinutes()}`,
            y: value
        };
        
        var aux = this.state.temperatureList;
        aux.push(object);
        this.setState({temperature: value, temperatureList: aux});
    }

    getHumidity(){
        var min = Math.ceil(40);
        var max = Math.floor(25);
        var value = Math.floor(Math.random() * (max - min)) + min;

        var date = new Date();
        var object = {
            label: `${date.getHours() > 9 ? date.getHours() : "0" + date.getHours()}:${date.getMinutes() > 9 ? date.getMinutes() : "0" + date.getMinutes()}`,
            y: value
        };
        
        var aux = this.state.humidityList;
        aux.push(object);
        this.setState({humidity: value, humidityList: aux});
    }

    render() {
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