import React, { Component } from 'react';
import TopBar from '../topbar/topbar.component'
import SideBar from '../sidebar/sidebar.component'
import Dock from '../dock/dock.component'

class Actions extends Component {
  constructor(){
    super();
    this.state = {chosenCondition:null, chosenMeasurement:null, value:0};
    this.setCondition = this.setCondition.bind(this);
    this.setMeasurement = this.setMeasurement.bind(this);
    this.setValue = this.setValue.bind(this);
  }
  setCondition = (condition) => {
    console.log("chosen Condition: ", condition);
    this.setState({chosenCondition: condition});
  }
  setMeasurement = (measurement) => {
    console.log("chosen measurement: ", measurement);
    this.setState({chosenMeasurement:measurement});
  }
  setValue = (value) => {
    console.log("value received: ", value);
    this.setState({value});
  }
  submitForm = (e=null) =>{
    if(this.state.chosenCondition!=null && this.state.chosenMeasurement!=null && this.value!=0){
      window.localStorage.setItem("condition", this.state.chosenCondition);
      window.localStorage.setItem("measurements", this.state.chosenMeasurement);
      window.localStorage.setItem("value", this.value);
    }
  }
  render() {
    return (
      <div className="App">
        <div className="row">
          <TopBar setCondition={this.setCondition}/>
        </div>
        <div className="row">
          <div className="col-sm-3">
            <div className="row" style={{paddingTop:'15vh'}}>
              <div className="col-sm-12">
                <SideBar setMeasurement={this.setMeasurement}/>
              </div>
            </div>
          </div>
          <div className="col-sm-6">
            <div className="row" style={{paddingTop:'25vh'}}>
              <div className="col-sm-4" id="measurement" style={{maxWidth:'200px', padding:'30px', minHeight:'100px', border:'1px solid black', marginLeft:'5px'}}>
                <span>Place Measurement Device Here</span>
              </div>
              <div className="col-sm-4" id="condition" style={{maxWidth:'200px', padding:'30px', minHeight:'100px', border:'1px solid black', marginLeft:'5px'}}>
                <span>Place Condition Here</span>
              </div>
              <div className="col-sm-4" style={{marginTop:'30px'}}>
                <input value={this.state.value} type="text" onChange={e=>this.setValue(e.target.value)} id="value"/>
              </div>
            </div>
          </div>
          <div className="col-sm-3">
            <button style={{marginTop:'30vh'}} onClick={this.submitForm}>Submit</button>
          </div>
        </div>
      </div>
    );
  }
}

export default Actions;
