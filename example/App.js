// @flow
import React, { Component } from "react";
import { StyleSheet, ScrollView, Dimensions } from "react-native";
import { Surface, Shape, Group, Text } from "@react-native-community/art";

const SURFACE_DIMENSIONS = Dimensions.get("window").width;
const HEART_SHAPE =
  "M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z";
const PINK = "#d39494";

export default function App() {
  return (
    <ScrollView contentContainerStyle={styles.container}>
      <Surface
        width={SURFACE_DIMENSIONS}
        height={SURFACE_DIMENSIONS}
        style={styles.surface}
      >
        <Group x={SURFACE_DIMENSIONS / 2 - 50} y={SURFACE_DIMENSIONS / 2 - 50}>
          <Shape d={HEART_SHAPE} fill={PINK} />
        </Group>
      </Surface>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: {
    flexGrow: 1,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#F5FCFF"
  },
  surface: {
    backgroundColor: "transparent"
  }
});
