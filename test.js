const testLoadLibrary = require('./build/Release/test_module');

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

const result = testLoadLibrary(lib);
console.log(result);
process.exit(result ? 0 : 1);
