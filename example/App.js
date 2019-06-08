// @flow
import React from 'react';
import {StyleSheet, ScrollView, SafeAreaView} from 'react-native';
import Heart from './components/Heart';
import CustomShape from './components/CustomShape';
import CustomText from './components/CustomText';

export default function App() {
  return (
    <SafeAreaView>
      <ScrollView contentContainerStyle={styles.container}>
        <CustomText />
        <Heart />
        <CustomShape />
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
