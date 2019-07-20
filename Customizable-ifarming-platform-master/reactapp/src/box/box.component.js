import React, { Component } from "react"
import Draggable from 'react-draggable';

export default class Box extends Component{
    constructor(props){
        super(props);
        this.state = {prev:undefined};
        this.eventLogger = this.eventLogger.bind(this);
        this.handleStart = this.handleStart.bind(this);
        this.handleDrag = this.handleDrag.bind(this);
        this.handleStop = this.handleStop.bind(this);
    }
    eventLogger = (e, data) => {
        console.log('Event: ', e);
        console.log('Data: ', data);
    };
    handleStop(e=null){
        console.log("received e: ", e);
        if(e.target.id!=this.props.typeOfValue){
            console.log("nope");
        }else{
            this.setState({prev: e.target});
            this.props.setValue(this.props.symbol);
        }
    }
    handleDrag(e=null){
        console.log("received e: ", e);
    }
    handleStart(e=null){
        console.log("received e in handlestart: ", e);
    }
    render(){
        return(
            <Draggable
                axis="both"
                handle=".handle"
                defaultPosition={{x: this.props.x, y: this.props.y}}
                position={null}
                grid={[50, 50]}
                scale={1}
                onStart={this.handleStart}
                onDrag={this.handleDrag}
                onStop={this.handleStop}>
                <div>
                    <div className="handle"><span style={{fontSize:40}}>{this.props.symbol}</span></div>
                </div>
            </Draggable>
        )
    }
}