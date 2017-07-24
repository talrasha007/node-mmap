const mmap = require('..');

const buffer = mmap.map('/tmp/test.mm', 1024 * 1024 * 8);
console.log(buffer.length);
console.log(buffer);

buffer.sync();