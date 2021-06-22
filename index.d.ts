declare module '@react-native-community/art' {
  type FlexAlignType = 'flex-start' | 'flex-end' | 'center' | 'stretch' | 'baseline';

  /**
   * Flex Prop Types
   * @see https://facebook.github.io/react-native/docs/flexbox.html#proptypes
   * @see LayoutPropTypes.js
   */
  interface FlexStyle {
    alignContent?:
      | 'flex-start'
      | 'flex-end'
      | 'center'
      | 'stretch'
      | 'space-between'
      | 'space-around';
    alignItems?: FlexAlignType;
    alignSelf?: 'auto' | FlexAlignType;
    aspectRatio?: number;
    borderBottomWidth?: number;
    borderLeftWidth?: number;
    borderRightWidth?: number;
    borderTopWidth?: number;
    borderWidth?: number;
    bottom?: number | string;
    flex?: number;
    flexBasis?: number | string;
    flexDirection?: 'row' | 'column' | 'row-reverse' | 'column-reverse';
    flexGrow?: number;
    flexShrink?: number;
    flexWrap?: 'wrap' | 'nowrap';
    height?: number | string;
    justifyContent?: 'flex-start' | 'flex-end' | 'center' | 'space-between' | 'space-around';
    left?: number | string;
    margin?: number | string;
    marginBottom?: number | string;
    marginHorizontal?: number | string;
    marginLeft?: number | string;
    marginRight?: number | string;
    marginTop?: number | string;
    marginVertical?: number | string;
    maxHeight?: number | string;
    maxWidth?: number | string;
    minHeight?: number | string;
    minWidth?: number | string;
    overflow?: 'visible' | 'hidden' | 'scroll';
    padding?: number | string;
    paddingBottom?: number | string;
    paddingHorizontal?: number | string;
    paddingLeft?: number | string;
    paddingRight?: number | string;
    paddingTop?: number | string;
    paddingVertical?: number | string;
    position?: 'absolute' | 'relative';
    right?: number | string;
    top?: number | string;
    width?: number | string;
    zIndex?: number;

    /**
     * @platform ios
     */
    direction?: 'inherit' | 'ltr' | 'rtl';
  }

  interface PerpectiveTransform {
    perspective: number;
  }

  interface RotateTransform {
    rotate: string;
  }

  interface RotateXTransform {
    rotateX: string;
  }

  interface RotateYTransform {
    rotateY: string;
  }

  interface RotateZTransform {
    rotateZ: string;
  }

  interface ScaleTransform {
    scale: number;
  }

  interface ScaleXTransform {
    scaleX: number;
  }

  interface ScaleYTransform {
    scaleY: number;
  }

  interface TranslateXTransform {
    translateX: number;
  }

  interface TranslateYTransform {
    translateY: number;
  }

  interface SkewXTransform {
    skewX: string;
  }

  interface SkewYTransform {
    skewY: string;
  }

  interface TransformsStyle {
    transform?: (
      | PerpectiveTransform
      | RotateTransform
      | RotateXTransform
      | RotateYTransform
      | RotateZTransform
      | ScaleTransform
      | ScaleXTransform
      | ScaleYTransform
      | TranslateXTransform
      | TranslateYTransform
      | SkewXTransform
      | SkewYTransform
    )[];
    transformMatrix?: Array<number>;
    rotation?: number;
    scaleX?: number;
    scaleY?: number;
    translateX?: number;
    translateY?: number;
  }

  // @see https://facebook.github.io/react-native/docs/view.html#style
  interface ViewStyle extends FlexStyle, TransformsStyle {
    backfaceVisibility?: 'visible' | 'hidden';
    backgroundColor?: string;
    borderBottomColor?: string;
    borderBottomLeftRadius?: number;
    borderBottomRightRadius?: number;
    borderBottomWidth?: number;
    borderColor?: string;
    borderLeftColor?: string;
    borderRadius?: number;
    borderRightColor?: string;
    borderRightWidth?: number;
    borderStyle?: 'solid' | 'dotted' | 'dashed';
    borderTopColor?: string;
    borderTopLeftRadius?: number;
    borderTopRightRadius?: number;
    borderTopWidth?: number;
    display?: 'none' | 'flex';
    opacity?: number;
    overflow?: 'visible' | 'hidden';
    shadowColor?: string;
    shadowOffset?: {width: number; height: number};
    shadowOpacity?: number;
    shadowRadius?: number;
    elevation?: number;
    testID?: string;
  }

  type Falsy = undefined | null | false;
  interface RecursiveArray<T> extends Array<T | RecursiveArray<T>> {}
  /** Keep a brand of 'T' so that calls to `StyleSheet.flatten` can take `RegisteredStyle<T>` and return `T`. */
  type RegisteredStyle<T> = number & {__registeredStyleBrand: T};
  type StyleProp<T> =
    | T
    | RegisteredStyle<T>
    | RecursiveArray<T | RegisteredStyle<T> | Falsy>
    | Falsy;

  export interface ARTShapeProps {
    d: string | PathStatic;
    strokeWidth?: number;
    strokeDash?: number[];
    stroke?: string;
    fill?: string | LinearGradientStatic;
    strokeCap?: 'square' | 'butt' | 'round';
    transform?: string | TransformStatic;
  }

  export interface ARTSurfaceProps {
    style?: StyleProp<ViewStyle>;
    width: number;
    height: number;
  }

  export interface ARTTextProps {
    font: string;
    fill?: string;
    x: number;
    y: number;
    alignment?: 'left' | 'center' | 'right';
  }

  export interface ARTGroupProps {
    transform?: string | TransformStatic;
  }

  interface ShapeStatic extends React.ComponentClass<ARTShapeProps> {}

  interface SurfaceStatic extends React.ComponentClass<ARTSurfaceProps> {}

  interface PathStatic {
    new (): PathStatic;
    move(dx: number, dy: number): PathStatic;
    moveTo(x: number, y: number): PathStatic;
    line(dx: number, dy: number): PathStatic;
    lineTo(x: number, y: number): PathStatic;
    arc(dx: number, dy: number, radius: number): PathStatic;
    arcTo(x: number, y: number, radius: number): PathStatic;
    close(): PathStatic;
  }

  interface TransformStatic {
    new (): TransformStatic;
    move(dx: number, dy: number): TransformStatic;
    rotate(angle: number, cx?: number, cy?: number): TransformStatic;
  }

  export interface ARTTextStatic extends React.ComponentClass<ARTTextProps> {}

  interface GroupStatic extends React.ComponentClass<ARTGroupProps> {}

  interface LinearGradientStatic extends React.ComponentClass<ARTGroupProps> {
    new (
      stops: {[stop: string]: string},
      x0: number,
      y0: number,
      x1: number,
      y1: number,
    ): LinearGradientStatic;
  }

  export var Shape: ShapeStatic;
  export type Shape = ShapeStatic;
  export var Surface: SurfaceStatic;
  export type Surface = SurfaceStatic;
  export var Text: ARTTextStatic;
  export type Text = ARTTextStatic;
  export var Path: PathStatic;
  export type Path = PathStatic;
  export var Group: GroupStatic;
  export type Group = GroupStatic;
  export var LinearGradient: LinearGradientStatic;
  export type LinearGradient = LinearGradientStatic;
  export var Transform: TransformStatic;
  export type Transform = TransformStatic;
}
