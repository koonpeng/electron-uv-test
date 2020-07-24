const testLoadLibrary = require('.');

const result = testLoadLibrary();
console.log(result);
process.exit(result ? 0 : 1);
