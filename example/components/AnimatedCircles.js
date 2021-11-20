// @flow
import React from 'react';
import {Animated, Easing, StyleSheet, Dimensions} from 'react-native';
import {Surface, Shape, Group} from '@react-native-community/art';

/*
An example of Animated Shapes

Animated uses 'setNativeProps' on the AnimatedShape, preventing rerendering
for each step in the animation
*/

const CIRCLE = 'M 25, 50 a 25,25 0 1,1 50,0 a 25,25 0 1,1 -50,0';

export default function AnimatedCircles() {
  const surfaceWidth = Dimensions.get('window').width;

  const AnimatedShape = Animated.createAnimatedComponent(Shape);

  const [animatedOpacity] = React.useState(new Animated.Value(1));

  const blink = React.useCallback(
    toValue =>
      Animated.timing(animatedOpacity, {
        duration: 900,
        easing: Easing.linear,
        toValue,
      }).start(() => blink(toValue === 0 ? 1 : 0)),
    [animatedOpacity],
  );

  React.useEffect(() => {
    blink(0);
  }, [blink]);

  return (
    <Surface width={surfaceWidth} height={100} style={styles.surface}>
      <Group x={25} y={0}>
        <AnimatedShape
          d={CIRCLE}
          fill={'#61DAFB'}
          opacity={animatedOpacity.interpolate({
            inputRange: [0, 1, 2],
            outputRange: [1, 0, 0],
          })}
        />
      </Group>
      <Group x={surfaceWidth / 2 - 50} y={0}>
        <AnimatedShape
          d={CIRCLE}
          fill={'#61DAFB'}
          opacity={animatedOpacity.interpolate({
            inputRange: [0, 1],
            outputRange: [0, 1],
          })}
        />
      </Group>
      <Group x={surfaceWidth - 125} y={0}>
        <AnimatedShape
          d={CIRCLE}
          fill={'#61DAFB'}
          opacity={animatedOpacity.interpolate({
            inputRange: [0, 1],
            outputRange: [1, 0],
          })}
        />
      </Group>
    </Surface>
  );
}
const styles = StyleSheet.create({
  surface: {
    backgroundColor: '#000',
  },
});
