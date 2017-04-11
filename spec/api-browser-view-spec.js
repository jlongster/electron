'use strict'

const assert = require('assert')
const {closeWindow} = require('./window-helpers')

const {remote} = require('electron')
const {BrowserView, BrowserWindow} = remote

describe('View module', function () {
  var w = null

  beforeEach(function () {
    w = new BrowserWindow({
      show: false,
      width: 400,
      height: 400,
      webPreferences: {
        backgroundThrottling: false
      }
    })
  })

  afterEach(function () {
    return closeWindow(w).then(function () { w = null })
  })

  describe('BrowserView.setBackgroundColor()', function () {
    it('does not throw for valid args', function () {
      const view = new BrowserView()
      view.setBackgroundColor('#000')
    })

    it('throw for invalid args', function () {
      const view = new BrowserView()
      assert.throws(function () {
        view.setBackgroundColor(null)
      }, /conversion failure/)
    })
  })

  describe('BrowserView.setBounds()', function () {
    it('does not throw for valid args', function () {
      const view = new BrowserView()
      view.setBounds({ x: 0, y: 0, width: 1, height: 1 })
    })

    it('throw for invalid args', function () {
      const view = new BrowserView()
      assert.throws(function () {
        view.setBounds(null)
      }, /conversion failure/)
      assert.throws(function () {
        view.setBounds({})
      }, /conversion failure/)
    })
  })

  describe('BrowserWindow.setBrowserView()', function () {
    it('does not throw for valid args', function () {
      const view = new BrowserView()
      w.setBrowserView(view)
    })

    it('does not throw if called multiple times with same view', function () {
      const view = new BrowserView()
      w.setBrowserView(view)
      w.setBrowserView(view)
      w.setBrowserView(view)
    })
  })
})
