import React, { Component } from 'react';
import Box from '../box/box.component';

export default class TopBar extends Component {
    constructor(props){
        super(props);
    }
    render() {
      return (
        <div className="row">
            <div className="col-sm-3"></div>
            <div className="col-sm-2">
                <Box setValue={this.props.setCondition} typeOfValue={'condition'} x={-10} y={0} symbol={'<'}/>
            </div>
            <div className="col-sm-2">
                <Box setValue={this.props.setCondition} typeOfValue={'condition'} x={0} y={0} symbol={'='}/>
            </div>
            <div className="col-sm-2">
                <Box setValue={this.props.setCondition} typeOfValue={'condition'} x={10} y={0} symbol={'>'}/>
            </div>
            <div className="col-sm-3"></div>
        </div>
      );
    }
}