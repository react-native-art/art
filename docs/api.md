# API

## Surface

Container for all other ART components

|   Prop   |     Type     | Required |
| :------: | :----------: | :------: |
|  height  |   `number`   |    No    |
|  width   |   `number`   |    No    |
|  style   |    `any`     |    No    |
| children | `React.Node` |    No    |

```js
import {Dimensions} from 'react-native';
import {Surface} from '@react-native-community/art';

const SURFACE_DIMENSIONS = Dimensions.get('window').width;

function Heart() {
  return (
    <Surface width={SURFACE_DIMENSIONS} height={SURFACE_DIMENSIONS}>
      {renderARTShapes()}
    </Surface>
  );
}
```

## Group

Container to combine shapes or other groups into hierarchies that can be transformed as a set.

|       Prop        |       Type       | Required |
| :---------------: | :--------------: | :------: |
|  ...opacityProps  |  `OpacityProps`  |    No    |
| ...transformProps | `TransformProps` |    No    |
|     children      |   `React.Node`   |    No    |

```js
import {Dimensions} from 'react-native';
import {Surface, Group} from '@react-native-community/art';

const SURFACE_DIMENSIONS = Dimensions.get('window').width;

function GrouppedHearts() {
  return (
    <Surface width={SURFACE_DIMENSIONS} height={SURFACE_DIMENSIONS}>
      <Group>{renderARTGroupContents()}</Group>
    </Surface>
  );
}
```

## Shape

Used to draw arbitrary vector shapes from Path. Shape implements Transform as a mixin which means it has all transform methods available for moving, scaling and rotating a shape.

|       Prop        |             Type              | Required |
| :---------------: | :---------------------------: | :------: |
|  ...opacityProps  |        `OpacityProps`         |    No    |
| ...transformProps |       `TransformProps`        |    No    |
|       fill        |       `string | Brush`        |    No    |
|      stroke       |           `string`            |    No    |
|     strokeCap     | `'butt' | 'square' | 'round'` |    No    |
|    strokeDash     |        `Array<number>`        |    No    |
|    strokeJoin     | `'miter' | 'bevel' | 'round'` |    No    |
|    strokeWidth    |           `number`            |    No    |
|         d         |        `string | Path`        |    No    |
|       width       |           `number`            |    No    |
|      height       |           `number`            |    No    |
|     children      |         `React.Node`          |    No    |

```js
import {Dimensions} from 'react-native';
import {Surface, Shape} from '@react-native-community/art';

const SURFACE_DIMENSIONS = Dimensions.get('window').width;

function Heart() {
  return (
    <Surface width={SURFACE_DIMENSIONS} height={SURFACE_DIMENSIONS}>
      <Shape
        d="M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z"
        fill="#d39494"
      />
    </Surface>
  );
}
```

## Text

Text component creates a shape based on text content using native text rendering.

|       Prop        |             Type              | Required |
| :---------------: | :---------------------------: | :------: |
| ...transformProps |       `TransformProps`        |    No    |
|  ...opacityProps  |        `OpacityProps`         |    No    |
|       fill        |       `string | Brush`        |    No    |
|      stroke       |           `string`            |    No    |
|     strokeCap     | `'butt' | 'square' | 'round'` |    No    |
|    strokeDash     |        `Array<number>`        |    No    |
|    strokeJoin     | `'miter' | 'bevel' | 'round'` |    No    |
|    strokeWidth    |           `number`            |    No    |
|       width       |           `number`            |    No    |
|      height       |           `number`            |    No    |
|     alignment     | `'center' | 'left' | 'right'` |    No    |
|       font        |        `string | Font`        |    No    |
|       path        |        `string | Path`        |    No    |
|     children      |   `string | Array<string>`    |    No    |

## Path

Generate an SVG `path` that you can pass to the `Shape` element.

`constructor`

```js
new Path(path: string | Path)
```

`Path.move`

Move current context from current position by `x` and `y`.

```js
function move(x: number, y: number): Path;
```

`Path.moveTo`

Move current context from current position to absolute coordinate `x` and `y`.

```js
function moveTo(x: number, y: number): Path;
```

`Path.line`

Draw a line from current position to relative `x` and `y`.

```js
function line(x: number, y: number): Path;
```

`Path.lineTo`

Draw a line from current poistion to absolute coordinate `x` and `y`.

```js
function lineTo(x: number, y: number): Path;
```

`Path.curve`

Draw a cubic bezier curve to relative position.

```js
function curve(
  x1: number,
  y1: number,
  x2: number,
  y2: number,
  deltaX: number,
  deltaY: number,
): Path;
```

`Path.curveTo`

Draw a bezier curve to absolute position.

```js
function curveTo(
  x1: number,
  y1: number,
  x2: number,
  y2: number,
  deltaX: number,
  deltaY: number,
): Path
```

`Path.arc`

Draw an arc with specific arguments.

```js
function arc(
  x: number,
  y: number,
  xRadius: number,
  yRadius: number,
  outer?: boolean,
  counterClockWise?: boolean,
  rotation?: number,
): Path;
```

`Path.arcTo`

Draw an arc to absolute coordinates.

```js
function arcTo(
  x: number,
  y: number,
  xRadius: number,
  yRadius: number,
  outer?: boolean,
  counterClockWise?: boolean,
  rotation?: number,
): Path;
```

`Path.counterArc`

Same as `arc`, opposite clockwise.

`Path.counterArcTo`

Same as `arcTo`, opposite clockwise.

`Path.close`

Draws a line to the first point in the current sub-path and begins a new sub-path.

```js
function close(): Path;
```

`Path.reset`

Reset the current path.

```js
function reset(): Path;
```

`Path.toJSON`

Return the current path points, which can be used on Shape d attribute.

```js
function toJSON() => Array<number | string>;
```

## LinearGradient

Creates a linear gradient fill.

```js
function LinearGradient({
  stops: GradientStops,
  x1?: number,
  y1?: number,
  x2?: number,
  y2?: number,
}): Brush;
```

## RadialGradient

Creates a radial gradient fill.

```js
function RadialGradient({
  stops: GradientStops,
  x1?: number,
  y1?: number,
  x2?: number,
  y2?: number,
}): Brush;
```

## Pattern

Creates a pattern fill.

> _This component is not exactly working as expected. [More context here.](https://github.com/facebook/react-native/issues/1462)_

```js
function Pattern(
  url: number | string,
  width: number,
  height: number,
  left?: number,
  top?: number,
): Brush;
```

## Transform

Generate a transform that can applied to ART elements.

[Transform docs](https://github.com/sebmarkbage/art/blob/842d2d56c6436adc0bbb0c065a296f295b95bc0a/docs/ART/ART.Transform.md)


## ClippingRectangle

Control display area of graphic.

|      Prop       |      Type      | Required |
| :-------------: | :------------: | :------: |
| ...opacityProps | `OpacityProps` |    No    |
|        x        |    `number`    |    No    |
|        y        |    `number`    |    No    |
|      width      |    `number`    |    No    |
|     height      |    `number`    |    No    |
|    children     |  `React.Node`  |    No    |

```js
import React from 'react';
import {
  Surface,
  ClippingRectangle,
  Shape,
  Path,
} from '@react-native-community/art';

function Component() {
  return (
    <Surface width={200} height={200}>
      <ClippingRectangle width={20} height={20} x={100} y={100}>
        <Shape
          d={new Path().moveTo(0, 0).lineTo(200, 200)}
          stroke="black"
          strokeWidth={10}
        />
      </ClippingRectangle>
    </Surface>
  );
}
```

## Common types

### OpacityProps

|  Prop   |   Type    | Required |
| :-----: | :-------: | :------: |
| visible | `boolean` |    No    |
| opacity | `number`  |    No    |

### TransformObject

| Prop |   Type   | Required |
| :--: | :------: | :------: |
|  y   | `number` |    No    |
|  x   | `number` |    No    |
|  yy  | `number` |    No    |
|  xx  | `number` |    No    |
|  yx  | `number` |    No    |
|  xy  | `number` |    No    |

### TransformProps

|   Prop    |       Type        | Required |
| :-------: | :---------------: | :------: |
|  scaleX   |     `number`      |    No    |
|  scaleY   |     `number`      |    No    |
|   scale   |     `number`      |    No    |
|     x     |     `number`      |    No    |
|     y     |     `number`      |    No    |
| rotation  |     `number`      |    No    |
|  originX  |     `number`      |    No    |
|  originY  |     `number`      |    No    |
| transform | `TransformObject` |    No    |

### Font

|    Prop    |  Type  | Required |
| :--------: | :----: | :------: |
| fontFamily | string |   Yes    |
|  fontSize  | number |    No    |
| fontWeight | string |    No    |
| fontStyle  | string |    No    |
