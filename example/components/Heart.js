// @flow
import React from 'react';
import {StyleSheet, Dimensions} from 'react-native';
import {
  Surface,
  Shape,
  Group,
  RadialGradient,
} from '@react-native-community/art';

const HEART_SHAPE =
  'M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z';

export default function Heart() {
  const surfaceDimensions = Dimensions.get('window').width;
  const gradient = new RadialGradient(
    {
      '.1': 'red',
      '0.4': '#8c0505',
      '1': '#d39494',
    },
    50,
    50,
    20,
    20,
    50,
    50,
  );

  return (
    <Surface
      width={surfaceDimensions}
      height={surfaceDimensions / 2}
      style={styles.surface}>
      <Group
        x={surfaceDimensions / 2 - 50}
        y={surfaceDimensions / 4 - 50}
        visible={true}>
        <Shape
          d={HEART_SHAPE}
          strokeWidth={5}
          stroke={'#00ff00'}
          fill={gradient}
          visible={true}
        />
      </Group>
    </Surface>
  );
}

const styles = StyleSheet.create({
  surface: {
    backgroundColor: 'black',
  },
});
