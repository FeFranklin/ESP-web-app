import './App.css';
import { useState } from 'react';

function App() {
  const [res, setRes] = useState("Not connected.");

  const onClick = (bool) => {
    const addr = bool ? 'http://192.168.0.238:80/on' : 'http://192.168.0.238:80/off';
    const requestOptions = {
      method: 'POST',
      headers: {
        "Content-Type": "text/plain",
        "Access-Control-Allow-Headers": "*",
        "Access-Control-Allow-Origin0": "*",
      }
    };
    fetch(addr, requestOptions)
      .then(res => res.text())
      .then(data => setRes(data));
  }

  const isConnected = () => {
    const requestOptions = {
      method: 'POST',
      headers: {
        "Content-Type": "text/plain",
        "Access-Control-Allow-Headers": "*",
        "Access-Control-Allow-Origin0": "*",
      }
    };
    fetch('http://192.168.0.238:80/connect', requestOptions)
      .then(res => res.text())
      .then(data => setRes(data));
  }

  return (
    <div className="App">
      <h3>Embbeded and Ambiest Systems ESP8266 Wi-Fi</h3>
      <div style={{marginBottom: '20px'}}>
        <h6>Check connection with ESP8266</h6>
        <button type="button" onClick={e => isConnected()}>Check</button>
      </div>
      <div style={{marginTop: '20px'}}>
        <button type="button" onClick={e => onClick(true)}>Turn ON LED</button>
        <button type="button" onClick={e => onClick(false)}>Turn OFF LED</button>
        <p>{res}</p>
      </div>
    </div>
  );
}

export default App;
