const testLoadLibrary = require('./build/Release/test_module');

module.exports = () => {
  const lib = (() => {
    switch (process.platform) {
      case 'linux':
        return `${__dirname}/build/Release/foo.so`;
      case 'win32':
        return `${__dirname}/build/Release/libfoo.dll`;
      default:
        throw new Error('unsupported os');
    }
  })();

  return testLoadLibrary(lib);
}
