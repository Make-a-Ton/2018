import React, {Component} from "react"

export default class Visualisations extends Component{
    constructor(props){
        super(props);
        this.generateGraphs = this.generateGraphs.bind(this);
    }
    generateGraphs(){
        
    }
    render(){
        return(
            <div className="VisualisationSection">
                <div className="banner" style={{backgroundColor:"black"}}>
                    <span style={{color:"white"}}>{this.props.heading}</span>
                </div>
                {this.generateGraphs()}
            </div>
        );
    }
}