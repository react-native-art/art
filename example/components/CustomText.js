import React from 'react';
import {Dimensions, StyleSheet} from 'react-native';
import {Surface, Text, Group} from '@react-native-community/art';

const SHADOW = {
  shadowOpacity: 0.5,
  shadowColor: 'blue',
  shadowRadius: 10,
  shadowOffset: {x: 4, y: 4},
};

export default function CustomText() {
  const surfaceWidth = Dimensions.get('window').width;
  const surfaceHeight = surfaceWidth / 3;

  return (
    <Surface width={surfaceWidth} height={surfaceHeight} style={styles.surface}>
      <Group x={surfaceWidth / 2 - 100} y={surfaceHeight / 2}>
        <Text
          font={'18px "Helvetica Neue", "Helvetica", Arial'}
          fill="#000000"
          {...SHADOW}>
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
