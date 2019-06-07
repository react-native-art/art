# `@react-native-community/art`

![Supports Android and iOS](https://img.shields.io/badge/platforms-android%20|%20ios-lightgrey.svg) ![MIT License](https://img.shields.io/npm/l/@react-native-community/slider.svg)

> NOTE: ART was extracted from core `react-native` as a part of "[Lean Core](https://github.com/facebook/react-native/issues/23313)" effort.

React Native library used for drawing vector graphics.

# Getting started

```sh
yarn add @react-native-community/art
```

or

```sh
npm install @react-native-community/art --save
```

### Automatic linking

```sh
react-native link @react-native-community/art
```

# Migrating from the core `react-native` module

To migrate to this module you need to follow all the installation instructions above and change your imports from:

```js
import { ART } from "react-native";
const { Surface, Shape } = ART;
```

to:

```js
import { Surface, Shape } from "@react-native-community/art";
```

# Documentation

// TODO

## License

The library is released under the MIT licence. For more information see `LICENSE`.
