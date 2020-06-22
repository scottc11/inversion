
// to run type 'node ./index/js' in terminal

const voltage = 4.98;
const max = 65535;
const octave = (max / voltage) / 12;

let notes = [];
let octaves = [];

for (let index = 1; index < 65; index++) {
  let val = ((max / voltage) / 12) * index;
  notes.push(Math.round(val));
}

for (let index = 1; index < 4; index++) {
  octaves.push(index * notes[11]);
}

// console.log("Notes", notes);
console.log("Octaves", octaves);



const DAC_VALUES = [
// A     A#     B      C      C#     D      D#     E      F      F#     G      G#
  1097,  2193,  3290,  4387,  5461,  6553,  7646,  8738,  9830,  10922, 12015, 13160,
  14256, 15353, 16450, 17546, 18643, 19739, 20836, 21933, 23029, 24126, 25223, 26319,
  27416, 28513, 29609, 30706, 31802, 32899, 33996, 35092, 36189, 37286, 38382, 39479, 
  40576, 41672, 42769, 43865, 44962, 46059, 47155, 48252, 49349, 50445, 51542, 52639, 
  53735, 54832, 55928, 57025, 58122, 59218, 60315, 61412, 62508, 63605, 64702
//                                   N/A    N/A    N/A    N/A    N/A    N/A
];

console.log(DAC_VALUES.length);

let dacMap = [];
let index = 0;
let octaveAdder = 0;

while (octaveAdder < 48) {
  index = octaveAdder;
  while (index < 16 + octaveAdder) {
    let subArray = [ DAC_VALUES[index], DAC_VALUES[index + 1], DAC_VALUES[index + 2] ];
    dacMap.push(subArray);  
    index += 2;
  }
  octaveAdder += 12
}

console.log(dacMap);