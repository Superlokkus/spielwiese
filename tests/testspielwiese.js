"use strict";

const addon = require('bindings')('spielwiese');
let assert = require("assert");
const expect = require('expect.js');

const testValues1 = function (value) {
    assert.equal(42 * 5, value);
};

describe("Spielwiese Addon", function () {
    it("should return 'world'", function () {
        const result = addon.hello();
        assert.equal(result, "world");
    });

    it("should return a promise on PromiseMethod", function () {
        let result = addon.PromiseMethod(42);
        expect(result).to.be.a(Promise);
        return result.then(testValues1);
    });
});