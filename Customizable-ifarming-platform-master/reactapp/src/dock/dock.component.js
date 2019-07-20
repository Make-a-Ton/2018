import React, {Component} from 'react'

export default class Dock extends Component{
    render(){
        return(
            <div style={{backgroundColor:"grey", position:'fixed', top:'50%', bottom:'50%', left:'40%', right:'50%', height: '300px', width:'400px', margin:'auto'}}>
                <span style={{padding:'50%'}}>
                    drag and drop here
                </span>
            </div>
        )
    }
}