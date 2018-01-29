const notes = [0, 0, 2, 4, 5, 7, 9, 11, 12, -1, 12, 11, 9, 7, 5, 4, 2, 0, -1, -1, -1,
               0, 4, 7, 12, 7, 4, 0];

const state = {
  i: 0,
  playing: 1,
}

function usOfPitch(pitch) {
  if (pitch == -1) return 0;
  const negPitch = 12 - pitch;
  const realDelay = 3000 * Math.pow(2, negPitch / 12) // us
  const residual = realDelay - 3000;
  return Math.floor(residual + 1);
}

function step() {
  if (state.i >= notes.length) return;
  if (state.playing) {
    console.log(usOfPitch(notes[state.i]));
    state.playing = 0;
    setTimeout(step, 100);
  }
  else {
    console.log(0);
    state.playing = 1;
    state.i++;
    setTimeout(step, 25);
  }

}

console.log("0\n0\n0");
setTimeout(step, 1000);
