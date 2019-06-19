declare module 'art/core/color' {
  export type ColorType = 'hex' | 'rgb' | 'hsb' | 'hsl';
  export interface ARTColor {
    isColor: true;
    red: string;
    green: string;
    blue: string;
    alpha: string;
  }

  export default class Color {
    red: number;
    green: number;
    blue: number;
    alpha: string;
    constructor(color: ARTColor | string | number, type?: ColorType);
  }
}
