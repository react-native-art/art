/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 */

import Class from 'art/core/class';
import Path from 'art/core/path';

type MoveFn = (x: number, y: number) => PathType;
type LineFn = (x: number, y: number) => PathType;
type CurveFn = (
  x1: number,
  y1: number,
  x2: number,
  y2: number,
  deltaX: number,
  deltaY: number,
) => PathType;

type ArcFn = (
  x: number,
  y: number,
  xRadius: number,
  yRadius: number,
  outer?: boolean,
  counterClockWise?: boolean,
  rotation?: number,
) => PathType;

interface PathType {
  new (path: string | PathType): PathType;
  move: MoveFn;
  moveTo: MoveFn;
  line: LineFn;
  lineTo: LineFn;
  curve: CurveFn;
  curveTo: CurveFn;
  arc: ArcFn;
  arcTo: ArcFn;
  counterArc: ArcFn;
  counterArcTo: ArcFn;
  close: () => PathType;
  reset: () => PathType;
  toJSON: () => Array<number | string>;
}

const MOVE_TO = 0;
const CLOSE = 1;
const LINE_TO = 2;
const CURVE_TO = 3;
const ARC = 4;

// TODO: Refactor to class
const SerializablePath = Class(Path, {
  initialize: function(path: string | typeof SerializablePath) {
    this.reset();
    if (path instanceof SerializablePath) {
      this.path = path.path.slice(0);
    } else if (path) {
      this.push(path);
    }
  },

  onReset: function() {
    this.path = [];
  },

  onMove: function(_sx: number, _sy: number, x: number, y: number) {
    this.path.push(MOVE_TO, x, y);
  },

  onLine: function(_sx: number, _sy: number, x: number, y: number) {
    this.path.push(LINE_TO, x, y);
  },

  onBezierCurve: function(
    _sx: number,
    _sy: number,
    p1x: number,
    p1y: number,
    p2x: number,
    p2y: number,
    x: number,
    y: number,
  ) {
    this.path.push(CURVE_TO, p1x, p1y, p2x, p2y, x, y);
  },

  _arcToBezier: Path.prototype.onArc,

  onArc: function(
    sx: number,
    sy: number,
    ex: number,
    ey: number,
    cx: number,
    cy: number,
    rx: number,
    ry: number,
    sa: number,
    ea: number,
    ccw: boolean,
    rotation: number,
  ) {
    if (rx !== ry || rotation) {
      return this._arcToBezier(
        sx,
        sy,
        ex,
        ey,
        cx,
        cy,
        rx,
        ry,
        sa,
        ea,
        ccw,
        rotation,
      );
    }
    this.path.push(ARC, cx, cy, rx, sa, ea, ccw ? 0 : 1);
  },

  onClose: function() {
    this.path.push(CLOSE);
  },

  toJSON: function() {
    return this.path;
  },
});

export default SerializablePath as PathType;
