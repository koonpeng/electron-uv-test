const testModule = require('./build/Release/uv_module');

console.log(testModule.testLoadLibrary());
process.exit(0);
