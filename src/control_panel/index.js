"use strict";
// const axios = require("axios").default;

const URL = "http://localhost:6644";

const release_btn = document.getElementById("release_btn");
const acquire_btn = document.getElementById("acquire_btn");
const send_btn = document.getElementById("send_btn");

release_btn.addEventListener("click", function (e) {
    e.preventDefault();
    axios.get(`${URL}/release`);
});
acquire_btn.addEventListener("click", function (e) {
    e.preventDefault();
    axios.get(`${URL}/acquire`);
});

send_btn.addEventListener("click", function (e) {
    e.preventDefault();
    const content = document.getElementById("content_txt").value;
    if (content == "") {
        content = "0,0,0";
    }
    axios.post(`${URL}/motors`, `[${content}]`);
});
