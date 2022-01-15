import React, { useState } from "react";
import axios from "axios";
import logo from "./logo.svg";
import "./App.css";

function App() {
    const [state, setstate] = useState({
        aquired: false,
        value: "",
        dev: "192.168.100.179",
    });
    const URL = () => {
        const host = document.getElementById("host").value;
        if (!host) host = "localhost";
        return `http://${host}:6644`;
    };

    const acquire = () => {
        axios
            .get(`${URL()}/acquire`)
            .then((result) => {
                console.log(result);
                setstate({ aquired: true });
            })
            .catch((err) => {
                alert("Error!");
            });
    };

    const release = () => {
        axios
            .get(`${URL()}/release`)
            .then((result) => {
                console.log(result);
                setstate({ aquired: false });
            })
            .catch((err) => {
                alert("Error!");
            });
    };

    const update = () => {
        console.log("Syncing motors");
        const motors = [0, 1, 2, 3].map(
            (i) => document.getElementById(`motor${i}`).value
        );
        const values = `[${motors}]`;
        setstate({ value: values });
        axios
            .post(`${URL()}/motors`, values)
            .then((result) => {
                console.log(result);
            })
            .catch((err) => {
                alert("Error!", err);
            });
    };
    return (
        <div>
            <div className="header">
                <h1>Control Panel</h1>
                <h3>Debug/Demonstration Interface</h3>
            </div>
            {/* <div className="lineup">
                <div className="servo">
                    <canvas id="canvas0"></canvas>
                </div>
                <div className="servo">
                    <canvas id="canvas1"></canvas>
                </div>
                <div className="servo">
                    <canvas id="canvas2"></canvas>
                </div>
                <div className="servo">
                    <canvas id="canvas3"></canvas>
                </div>
            </div> */}
            <hr />
            <div>
                <div className="toolbar">
                    <div className="buttons">
                        <div>
                            <select
                                id="host"
                                onChange={(e) => {
                                    console.log(e.target.value);
                                    setstate({ dev: e.target.value });
                                }}
                            >
                                <option value="192.168.100.179">Remote</option>
                                <option value="localhost">localhost</option>
                            </select>
                            <button onClick={(e) => acquire()} id="acquire_btn">
                                Acquire
                            </button>
                            <button onClick={(e) => release()} id="release_btn">
                                Release
                            </button>
                        </div>
                        <div>
                            <div>
                                Aquired:{" "}
                                <span>{state.aquired ? "true" : "false"}</span>
                            </div>
                        </div>
                    </div>
                    <br />
                    <div className="controls">
                        {[0, 1, 2, 3].map((i) => (
                            <input
                                key={i}
                                type="number"
                                id={`motor${i}`}
                                max={100}
                                min={0}
                                defaultValue={0}
                                onChange={(e) => update()}
                            />
                        ))}
                    </div>
                </div>
            </div>
        </div>
    );
}

export default App;
