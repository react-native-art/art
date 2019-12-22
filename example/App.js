// @flow
import React from 'react';
import {StyleSheet, ScrollView, SafeAreaView} from 'react-native';
import Heart from './components/Heart';
import CustomShape from './components/CustomShape';
import CustomText from './components/CustomText';
import AnimatedCircles from './components/AnimatedCircles';

export default function App() {
  return (
    <SafeAreaView style={styles.container}>
      <ScrollView>
        <CustomText />
        <Heart />
        <CustomShape />
        <AnimatedCircles />
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flexGrow: 1,
    backgroundColor: '#F5FCFF',
  },
});
