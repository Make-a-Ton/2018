import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import firebase from "firebase";
import Actions from "./actions/actions.component"
import Visualisations from "./visualisations/visualisations.component"

class App extends Component {
  constructor(){
    super();
    var config = {
      apiKey: "AIzaSyA602G4coRQX91LaxuJeXIhWuaKDv5qmbY",
      authDomain: "makathon-58656.firebaseapp.com",
      databaseURL: "https://makathon-58656.firebaseio.com",
      projectId: "makathon-58656",
      storageBucket: "makathon-58656.appspot.com",
      messagingSenderId: "399336601292"
    };
    firebase.initializeApp(config);
    this.db = firebase.firestore();
    this.state = {data:undefined};
    this.generateVisualisations = this.generateVisualisations.bind(this);
  }

  componentWillMount(){
    let obj = {};
    this.db.collection('data').get()
    .then(querySnapshot=>{
      querySnapshot.forEach(doc=>{
        obj[doc.data().address] = obj[doc.data().address]? obj[doc.data().address]: [];
        obj[doc.data().address].push(doc.data());
      })
      for(let key in obj){
        obj[key] = obj[key].reduce((acc, ob)=>{
          acc[ob['deviceType']] = ob;
          return acc;
        }, {});
      }
      console.log("obj: ", obj);
      this.setState({data: obj});
    }).catch(err=>{
      console.error("error in fetching data: ", err);
    });
  }

  generateVisualisations(){
    let ToReturn = [];
    for(let key in this.state.data){
      console.log("key in console: ", key);
      ToReturn.push(
        <Visualisations key={key} data={this.state.data[key]} heading={key} />
      )
    }
    return ToReturn;
  }
  
  render() {
    console.log("data: ", this.state.data);
    return (
      <div className="App">
        <nav className="navbar">
          
        </nav>
        {this.generateVisualisations()}
        <Actions/>
      </div>
    );
  }
}

export default App;
