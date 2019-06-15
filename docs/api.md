# API

## Surface

Container for all other ART components

|   Prop   |     Type     | Default |
| :------: | :----------: | :-----: |
|  height  |   `number`   |   `0`   |
|  width   |   `number`   |   `0`   |
|  style   |    `any`     |   ---   |
| children | `React.Node` |   ---   |

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

|       Prop        |       Type       | Default |
| :---------------: | :--------------: | :-----: |
|  ...opacityProps  |  `OpacityProps`  |   ---   |
| ...transformProps | `TransformProps` |   ---   |
|     children      |   `React.Node`   |   ---   |

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

|       Prop        |              Type               |  Default  |
| :---------------: | :-----------------------------: | :-------: |
|  ...opacityProps  |         `OpacityProps`          |    ---    |
| ...transformProps |        `TransformProps`         |    ---    |
|       fill        |        `string \| Brush`        |    ---    |
|      stroke       |            `string`             |    ---    |
|     strokeCap     | `'butt' \| 'square' \| 'round'` | `'round'` |
|    strokeDash     |         `Array<number>`         |    ---    |
|    strokeJoin     | `'miter' \| 'bevel' \| 'round'` | `'round'` |
|    strokeWidth    |            `number`             |    `1`    |
|         d         |        `string \| Path`         |    ---    |
|       width       |            `number`             |    `0`    |
|      height       |            `number`             |    `0`    |
|     children      |          `React.Node`           |    ---    |

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

|       Prop        |              Type               |  Default  |
| :---------------: | :-----------------------------: | :-------: |
| ...transformProps |        `TransformProps`         |    ---    |
|  ...opacityProps  |         `OpacityProps`          |    ---    |
|       fill        |        `string \| Brush`        |    ---    |
|      stroke       |            `string`             |    ---    |
|     strokeCap     | `'butt' \| 'square' \| 'round'` | `'round'` |
|    strokeDash     |         `Array<number>`         |    ---    |
|    strokeJoin     | `'miter' \| 'bevel' \| 'round'` | `'round'` |
|    strokeWidth    |            `number`             |    `1`    |
|       width       |            `number`             |    `0`    |
|      height       |            `number`             |    `0`    |
|     alignment     | `'center' \| 'left' \| 'right'` | `'left'`  |
|       font        |        `string \| Font`         |    ---    |
|       path        |        `string \| Path`         |    ---    |
|     children      |    `string \| Array<string>`    |    ---    |

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

|      Prop       |      Type      | Default |
| :-------------: | :------------: | :-----: |
| ...opacityProps | `OpacityProps` |   ---   |
|        x        |    `number`    |   `0`   |
|        y        |    `number`    |   `0`   |
|      width      |    `number`    |   `0`   |
|     height      |    `number`    |   `0`   |
|    children     |  `React.Node`  |   ---   |

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

|  Prop   |   Type    | Default |
| :-----: | :-------: | :-----: |
| visible | `boolean` | `true`  |
| opacity | `number`  |   ---   |

### TransformObject

| Prop |   Type   | Default |
| :--: | :------: | :-----: |
|  y   | `number` |   `0`   |
|  x   | `number` |   `0`   |
|  yy  | `number` |   `1`   |
|  xx  | `number` |   `1`   |
|  yx  | `number` |   `0`   |
|  xy  | `number` |   `0`   |

### TransformProps

|   Prop    |       Type        | Default |
| :-------: | :---------------: | :-----: |
|  scaleX   |     `number`      |   `1`   |
|  scaleY   |     `number`      |   `1`   |
|   scale   |     `number`      |   ---   |
|     x     |     `number`      |   `0`   |
|     y     |     `number`      |   `0`   |
| rotation  |     `number`      |   `0`   |
|  originX  |     `number`      |   ---   |
|  originY  |     `number`      |   ---   |
| transform | `TransformObject` |   ---   |

### Font

|    Prop    |   Type   | Default |
| :--------: | :------: | :-----: |
| fontFamily | `string` |   ---   |
|  fontSize  | `number` |  `12`   |
| fontWeight | `string` | `'400'` |
| fontStyle  | `string` |   ---   |
