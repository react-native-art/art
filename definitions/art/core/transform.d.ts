declare module 'art/core/transform' {
  interface TransformObject {
    y?: number;
    x?: number;
    yy?: number;
    xx?: number;
    yx?: number;
    xy?: number;
  }

  export default class Transform {
    transform:
      | ((
          xx: number,
          yx: number,
          xy: number,
          yy: number,
          x: number,
          y: number,
        ) => Transform)
      | ((transform: TransformObject) => Transform);
  }
}
