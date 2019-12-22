/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 */

import * as React from 'react';
import PropTypes from 'prop-types';
import invariant from 'invariant';
import {NativeGroup} from './nativeComponents';
import {translatePropsToNativeProps} from './helpers';
import type {OpacityProps, TransformProps, ShadowProps} from './types';

export type GroupProps = OpacityProps &
  ShadowProps &
  TransformProps & {
    children: React.Node,
  };

const nativePropList = ['opacity', 'transform'];

export default class Group extends React.Component<GroupProps> {
  static contextTypes = {
    isInSurface: PropTypes.bool.isRequired,
  };

  _rootComponent = null;

  setNativeProps(newProps: $Shape<GroupProps>) {
    if (this._rootComponent && newProps) {
      // newProps will only include what is changed, but we need existing props for some translations:
      const nativeProps = translatePropsToNativeProps(
        ({
          ...this.props,
          ...newProps,
        }: GroupProps),
        nativePropList,
      );
      // $FlowFixMe
      this._rootComponent.setNativeProps(nativeProps);
    }
  }

  render() {
    invariant(
      this.context.isInSurface,
      'ART: <Group /> must be a child of a <Surface />',
    );
    const nativeProps = translatePropsToNativeProps(this.props, nativePropList);

    return <NativeGroup {...nativeProps}>{this.props.children}</NativeGroup>;
  }
}
