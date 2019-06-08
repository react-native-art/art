// @flow
import React from 'react';
import {StyleSheet, Dimensions} from 'react-native';
import {
  Surface,
  Shape,
  Group,
  Path,
  Transform,
  LinearGradient,
} from '@react-native-community/art';

const SURFACE_WIDTH = Dimensions.get('window').width;
const SURFACE_HEIGHT = SURFACE_WIDTH / 2;

export default function CustomShape() {
  const gradient = new LinearGradient(
    {
      '.5': 'blue',
      '1': 'black',
    },
    0,
    0,
    250,
    250,
  );

  const path = new Path()
    .line(40, 200)
    .line(150, 80)
    .line(150, -80)
    .line(40, -200)
    .line(-190, 120);

  return (
    <Surface
      width={SURFACE_WIDTH}
      height={SURFACE_HEIGHT}
      style={styles.surface}>
      <Group
        transform={new Transform().scale(0.5, 0.5)}
        x={SURFACE_WIDTH / 2 - 90}
        y={SURFACE_HEIGHT / 2 - 70}>
        <Shape d={path} fill={gradient} />
      </Group>
    </Surface>
  );
}
const styles = StyleSheet.create({
  surface: {
    backgroundColor: '#d39494',
  },
});
