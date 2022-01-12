import React, { useState } from "react";
import axios from "axios";
import logo from "./logo.svg";
import "./App.css";

const URL = "http://localhost:6644";

function App() {
    const [state, setstate] = useState({
        aquired: false,
        value: "",
    });

    const send = () => {
        axios
            .post(`${URL}/motors`, `[${state.value}]`)
            .then((result) => {
                console.log(result);
            })
            .catch((err) => {
                throw err;
            });
    };

    const acquire = () => {
        axios
            .get(`${URL}/acquire`)
            .then((result) => {
                console.log(result);
            })
            .catch((err) => {
                throw err;
            });
    };

    const release = () => {
        axios
            .get(`${URL}/release`)
            .then((result) => {
                console.log(result);
            })
            .catch((err) => {
                throw err;
            });
    };
    return (
        <div>
            <h1>Control Panel</h1>
            <h2>Debug/Demonstration Interface</h2>
            <div>
                <button onClick={(e) => acquire()} id={"acquire_btn"}>
                    Acquire
                </button>
                <button onClick={(e) => release()} id={"release_btn"}>
                    Release
                </button>
                <br />
                <hr></hr> <br />
                <input
                    value={state.value}
                    onChange={(e) => setstate({ value: e.target.value })}
                    type={"text"}
                    name={"content"}
                    id={"content_txt"}
                />
                <button onClick={(e) => send()} id={"send_btn"}>
                    Send
                </button>
            </div>
        </div>
    );
}

export default App;
