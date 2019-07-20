import React, { Component } from 'react';
import Box from '../box/box.component';

export default class SideBar extends Component {
    constructor(props){
        super(props);
    }
    render() {
      return (
        <div>
            <div className="row">
                <div className="col-sm-12">
                    <Box setValue={this.props.setMeasurement} typeOfValue={'measurement'} x={-30} y={0} symbol={'Temperature'}/>
                </div>
            </div>
            <div className="row">
                <div className="col-sm-2">
                    <Box setValue={this.props.setMeasurement} typeOfValue={'measurement'} x={20} y={0} symbol={'Humidity'}/>
                </div>
            </div>
            <div className="row">
                <div className="col-sm-2">
                    <Box setValue={this.props.setMeasurement} typeOfValue={'measurement'} x={20} y={0} symbol={'Moisture'}/>
                </div>
            </div>
            <div className="row">
                <div className="col-sm-2">
                    <Box setValue={this.props.setMeasurement} typeOfValue={'measurement'} x={20} y={0} symbol={'Light'}/>
                </div>
            </div>
        </div>
      );
    }
}