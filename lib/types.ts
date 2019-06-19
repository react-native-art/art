/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 */
import Color from 'art/core/color';

export interface OpacityProps {
  visible?: boolean;
  opacity?: number;
}

export interface TransformProps {
  scaleX?: number;
  scaleY?: number;
  scale?: number;
  x?: number;
  y?: number;
  rotation?: number;
  originX?: number;
  originY?: number;
  transform?: {
    y?: number;
    x?: number;
    yy?: number;
    xx?: number;
    yx?: number;
    xy?: number;
  };
}

export type ColorType = string | number | Color;
export type StrokeJoin = 'miter' | 'bevel' | 'round';
export type StrokeCap = 'butt' | 'square' | 'round';
export type Alignment = 'center' | 'right' | 'left';

export interface Brush {
  _brush: Array<number>;
  _bb?: boolean;
}
export interface Font {
  fontFamily: string;
  fontSize?: number;
  fontWeight?: string;
  fontStyle?: string;
}

export type GradientStops = {[key: string]: ColorType} | Array<ColorType>;
