import { driver, By2 } from 'selenium-appium';
import { until } from 'selenium-webdriver';

const setup = require('../jest-windows/driver.setup');
jest.setTimeout(60000);

beforeAll(() => {
  return driver.startWithCapabilities(setup.capabilites);
});

afterAll(() => {
  return driver.quit();
});

describe('App Starts', () => {

  test('starts correctly', async () => {
    await driver.sleep(2000); // Expect 2s to be enough for the app to load.
    await driver.takeScreenshot();
  });

});

