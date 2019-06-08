import React from 'react';
import {Dimensions, StyleSheet} from 'react-native';
import {Surface, Text, Group} from '@react-native-community/art';

const SURFACE_WIDTH = Dimensions.get('window').width;
const SURFACE_HEIGHT = SURFACE_WIDTH / 3;

export default function CustomText() {
  return (
    <Surface
      width={SURFACE_WIDTH}
      height={SURFACE_HEIGHT}
      style={styles.surface}>
      <Group x={SURFACE_WIDTH / 2 - 100} y={SURFACE_HEIGHT / 2}>
        <Text font={'18px "Helvetica Neue", "Helvetica", Arial'} fill="#000000">
          React Native Community
        </Text>
      </Group>
    </Surface>
  );
}

const styles = StyleSheet.create({
  surface: {
    backgroundColor: 'transparent',
  },
});
