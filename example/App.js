// @flow
import React from 'react';
import {StyleSheet, ScrollView} from 'react-native';
import Heart from './components/Heart';

export default function App() {
  return (
    <ScrollView contentContainerStyle={styles.container}>
      <Heart />
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: {
    flexGrow: 1,
    backgroundColor: '#F5FCFF',
  },
});
