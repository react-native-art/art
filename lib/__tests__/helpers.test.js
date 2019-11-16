// @flow

import {
  childrenAsString,
  extractOpacity,
  extractStrokeJoin,
  extractStrokeCap,
  extractAlignment,
  translatePropsToNativeProps,
} from '../helpers';

describe('testing childrenAsString function', () => {
  it('returns a given string', () => {
    expect(childrenAsString('abc')).toBe('abc');
  });
  it('joins array of strings with \n', () => {
    let received = childrenAsString(['a', 'b', 'c', 'd']);
    expect(received.replace(new RegExp('\r?\n', 'g'), '')).toBe('abcd');
  });
});

describe('testing extractOpacity function', () => {
  it('returns 0 if visible is false', () => {
    expect(extractOpacity({visible: false})).toBe(0);
    expect(extractOpacity({visible: false, opacity: 1})).toBe(0);
    expect(extractOpacity({visible: false, opacity: 0.5})).toBe(0);
  });

  it('returns opacity if visible is true or undefined', () => {
    expect(extractOpacity({visible: true, opacity: 0.5})).toBe(0.5);
    expect(extractOpacity({opacity: 0.5})).toBe(0.5);
  });
});

describe('testing extractStrokeJoin', () => {
  const MITER = 0;
  const BEVEL = 2;
  const ROUND = 1;

  it('returns enum', () => {
    expect(extractStrokeJoin('miter')).toBe(MITER);
    expect(extractStrokeJoin('bevel')).toBe(BEVEL);
    expect(extractStrokeJoin('round')).toBe(ROUND);
  });

  it('default to round', () => {
    expect(extractStrokeJoin()).toBe(ROUND);
  });
});

describe('testing extractStrokeCap', () => {
  const BUTT = 0;
  const SQUARE = 2;
  const ROUND = 1;

  it('returns enum', () => {
    expect(extractStrokeCap('butt')).toBe(BUTT);
    expect(extractStrokeCap('square')).toBe(SQUARE);
    expect(extractStrokeCap('round')).toBe(ROUND);
  });

  it('default to round', () => {
    expect(extractStrokeCap()).toBe(ROUND);
  });
});

describe('testing extractAlignment', () => {
  const CENTER = 1;
  const RIGHT = 2;
  const LEFT = 0;

  it('returns enum', () => {
    expect(extractAlignment('center')).toBe(RIGHT);
    expect(extractAlignment('right')).toBe(CENTER);
    expect(extractAlignment('left')).toBe(LEFT);
  });

  it('default to left', () => {
    expect(extractAlignment()).toBe(LEFT);
  });
});

describe('testing translatePropsToNativeProps', () => {
  it('returns correct data for each prop', () => {
    // asserting the values in the returned object will fail if any of our helpers
    // are changed, but this is required to ensure the correct arguments are passed to
    // each of them at the right key:
    const props = {
      alignment: 'center',
      d: 'M 10,30 A 20,20 z',
      fill: '#D9003A',
      font: 'trebuchet',
      height: 100,
      opacity: 0.5,
      stroke: '#2DCD71',
      strokeCap: 'butt',
      strokeDash: 2,
      strokeJoin: 'miter',
      strokeWidth: 3,
      scale: 1.1,
      width: 200,
    };
    const nativeProps1 = translatePropsToNativeProps(props, [
      'alignment',
      'd',
      'fill',
      'frame',
      'opacity',
      'stroke',
      'strokeCap',
      'strokeDash',
      'strokeJoin',
      'strokeWidth',
      'transform',
    ]);
    expect(nativeProps1).toEqual({
      alignment: 2,
      d: [0, 10, 30],
      fill: [0, 0.8509803921568627, 0, 0.22745098039215686, 1],
      frame: {
        font: {
          fontFamily: 'trebuchet',
          fontSize: 12,
          fontStyle: 'normal',
          fontWeight: 'normal',
        },
        lines: [''],
      },
      opacity: 0.5,
      stroke: '#2dcd71',
      strokeCap: 0,
      strokeDash: 2,
      strokeJoin: 0,
      strokeWidth: 3,
      transform: [1.1, 0, 0, 1.1, 0, 0],
    });

    // test that we can select only a subset of nativeProps:
    const nativeProps2 = translatePropsToNativeProps(props, [
      'fill',
      'opacity',
      'stroke',
    ]);
    expect(nativeProps2).toEqual({
      fill: [0, 0.8509803921568627, 0, 0.22745098039215686, 1],
      opacity: 0.5,
      stroke: '#2dcd71',
    });
  });
});
