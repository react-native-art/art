/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 */

import * as React from 'react';
import Path from './ARTSerializablePath';
import {NativeText} from './nativeComponents';
import {translatePropsToNativeProps} from './helpers';
import type {
  TransformProps,
  OpacityProps,
  Alignment,
  Brush,
  StrokeCap,
  StrokeJoin,
  Font,
} from './types';

export type TextProps = TransformProps &
  OpacityProps & {
    fill?: string | Brush,
    stroke?: string,
    strokeCap?: StrokeCap,
    strokeDash?: mixed,
    strokeJoin?: StrokeJoin,
    strokeWidth?: mixed,
    children?: string | Array<string>,
    width: number,
    height: number,
    alignment?: Alignment,
    font?: string | Font,
    path?: string | Path,
  };

const nativePropList = [
  'alignment',
  'frame',
  'fill',
  'opacity',
  'path',
  'stroke',
  'strokeCap',
  'strokeDash',
  'strokeJoin',
  'strokeWidth',
  'transform',
];

export default class Text extends React.Component<TextProps> {
  static defaultProps = {
    strokeWidth: 1,
    width: 0,
    height: 0,
  };

  _rootComponent = null;

  setNativeProps(newProps: $Shape<TextProps>) {
    if (this._rootComponent && newProps) {
      // newProps will only include what is changed, but we need existing props for some translations:
      const nativeProps = translatePropsToNativeProps(
        ({
          ...this.props,
          ...newProps,
        }: TextProps),
        nativePropList,
      );
      // $FlowFixMe
      this._rootComponent.setNativeProps(nativeProps);
    }
  }

  render() {
    const nativeProps = translatePropsToNativeProps(this.props, nativePropList);

    return (
      <NativeText
        ref={component => (this._rootComponent = component)}
        {...nativeProps}
      />
    );
  }
}
