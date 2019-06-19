import {childrenAsString, extractOpacity, extractStrokeJoin, extractStrokeCap, extractAlignment} from '../helpers';

describe('testing childrenAsString function', () => {
  it('returns a given string', () => {
    expect(childrenAsString('abc')).toBe('abc');
  });
  it('returns empty string for invalid values', () => {
    expect(childrenAsString(null)).toBe('');
    expect(childrenAsString({})).toBe('');
    expect(childrenAsString(2)).toBe('');
  });
  it('joins array of strings with \n', () => {
    let received = childrenAsString(['a', 'b', 'c', 'd']);
    expect(received.replace(new RegExp('\r?\n', 'g'), '')).toBe('abcd');
  });
});

describe('testing extractOpacity function', () => {
  it('returns 0 if visible is false or null', () => {
    expect(extractOpacity({visible:false})).toBe(0);
    expect(extractOpacity({visible:false,opacity:1})).toBe(0);
    expect(extractOpacity({visible:false,opacity:0.5})).toBe(0);
    expect(extractOpacity({visible:null})).toBe(0);
  });
  it('returns opacity if visible is true', () => {
    expect(extractOpacity({visible:true, opacity:0.5})).toBe(0.5);
  });
  it('returns 1 if opacity is null', () => {
    expect(extractOpacity({visible:true, opacity:null})).toBe(1);
  });
});

describe('testing extractStrokeJoin', () => {
    //miter, bevel, round
    //miter: 0,
    //bevel: 2,
    //round: 1
    //defaultValue = 1;

    it('returns enum', () => {
        expect(extractStrokeJoin('miter')).toBe(0);
        expect(extractStrokeJoin('bevel')).toBe(2);
        expect(extractStrokeJoin('round')).toBe(1);
    })
    it('returns default value for any other input', () => {
        expect(extractStrokeJoin('abcde')).toBe(1);
    })
})

describe('testing extractStrokeCap', () => {
    //butt, square, round
    //butt: 0,
    //square: 2,
    //round: 1
    //defaultValue = 1;

    it('returns enum', () => {
        expect(extractStrokeCap('butt')).toBe(0);
        expect(extractStrokeCap('square')).toBe(2);
        expect(extractStrokeCap('round')).toBe(1);
    })
    it('returns default value for any other input', () => {
        expect(extractStrokeCap('abcde')).toBe(1);
    })
})

describe('testing extractAlignment', () => {
    //center, right, left
    //center: 1,
    //right: 2,
    //left: 0
    //defaultValue = 0;

    it('returns enum', () => {
        expect(extractAlignment('center')).toBe(2);
        expect(extractAlignment('right')).toBe(1);
        expect(extractAlignment('left')).toBe(0);
    })
    it('returns default value for any other input', () => {
        expect(extractAlignment('abcde')).toBe(0);
    })
})