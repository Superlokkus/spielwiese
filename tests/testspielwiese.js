"use strict";

const addon = require('bindings')('spielwiese');
let assert = require("assert");

describe("Spielwiese Addon", function () {
    it("should return 1337'", function () {
        const result = addon.hello();
        assert.equal(result, 1337);
    });
});