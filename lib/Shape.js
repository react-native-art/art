/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 */

import * as React from 'react';
import {NativeShape} from './nativeComponents';
import Path from './ARTSerializablePath';
import {translatePropsToNativeProps} from './helpers';
import type {
  TransformProps,
  OpacityProps,
  StrokeJoin,
  StrokeCap,
  Brush,
} from './types';

export type ShapeProps = TransformProps &
  OpacityProps & {
    fill?: string | Brush,
    stroke?: string,
    strokeCap?: StrokeCap,
    strokeDash?: Array<number>,
    strokeJoin?: StrokeJoin,
    strokeWidth: number,
    children?: React.Node,
    d?: string | Path,
    children?: string | Array<string>,
    width: number,
    height: number,
  };

const nativePropList = [
  'd',
  'fill',
  'opacity',
  'stroke',
  'strokeCap',
  'strokeDash',
  'strokeJoin',
  'strokeWidth',
  'transform',
];

export default class Shape extends React.Component<ShapeProps> {
  static defaultProps = {
    strokeWidth: 1,
    width: 0,
    height: 0,
  };

  _rootComponent = null;

  setNativeProps(newProps: $Shape<ShapeProps>) {
    if (this._rootComponent && newProps) {
      // newProps will only include what is changed, but we need existing props for some translations:
      const nativeProps = translatePropsToNativeProps(
        ({
          ...this.props,
          ...newProps,
        }: ShapeProps),
        nativePropList,
      );
      // $FlowFixMe
      this._rootComponent.setNativeProps(nativeProps);
    }
  }

  render() {
    const nativeProps = translatePropsToNativeProps(this.props, nativePropList);

    return (
      <NativeShape
        ref={component => (this._rootComponent = component)}
        {...nativeProps}
      />
    );
  }
}
