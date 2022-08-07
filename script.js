const wordList = ["the", "name", "of", "very", "to", "through", "and", "just", "a", "form", "in", "much", "is", "great", "it", "think", "you", "say", "that", "help", "he", "low", "was", "line", "for", "before", "on", "turn", "are", "cause", "with", "same", "as", "mean", "I", "differ", "his", "move", "they", "right", "be", "boy", "at", "old", "one", "too", "have", "does", "this", "tell", "from", "sentence", "or", "set", "had", "three", "by", "want", "hot", "air", "but", "well", "some", "also", "what", "play", "there", "small", "we", "end", "can", "put", "out", "home", "other", "read", "were", "hand", "all", "port", "your", "large", "when", "spell", "up", "add", "use", "even", "word", "land", "how", "here", "said", "must", "an", "big", "each", "high", "she", "such", "which", "follow", "do", "act", "their", "why", "time", "ask", "if", "men", "will", "change", "way", "went", "about", "light", "many", "kind", "then", "off", "them", "need", "would", "house", "write", "picture", "like", "try", "so", "us", "these", "again", "her", "animal", "long", "point", "make", "mother", "thing", "world", "see", "near", "him", "build", "two", "self", "has", "earth", "look", "father", "more", "head", "day", "stand", "could", "own", "go", "page", "come", "should", "did", "country", "my", "found", "sound", "answer", "no", "school", "most", "grow", "number", "study", "who", "still", "over", "learn", "know", "plant", "water", "cover", "than", "food", "call", "sun", "first", "four", "people", "thought", "may", "let", "down", "keep", "side", "eye", "been", "never", "now", "last", "find", "door", "any", "between", "new", "city", "work", "tree", "part", "cross", "take", "since", "get", "hard", "place", "start", "made", "might", "live", "story", "where", "saw", "after", "far", "back", "sea", "little", "draw", "only", "left", "round", "late", "man", "run", "year", "don't", "came", "while", "show", "press", "every", "close", "good", "night", "me", "real", "give", "life", "our", "few", "under", "stop", "open", "ten", "seem", "simple", "together", "several", "next", "vowel", "white", "toward", "children", "war", "begin", "lay", "got", "against", "walk", "pattern", "example", "slow", "ease", "center", "paper", "love", "often", "person", "always", "money", "music", "serve", "those", "appear", "both", "road", "mark", "map", "book", "science", "letter", "rule", "until", "govern", "mile", "pull", "river", "cold", "car", "notice", "feet", "voice", "care", "fall", "second", "power", "group", "town", "carry", "fine", "took", "certain", "rain", "fly", "eat", "unit", "room", "lead", "friend", "cry", "began", "dark", "idea", "machine", "fish", "note", "mountain", "wait", "north", "plan", "once", "figure", "base", "star", "hear", "box", "horse", "noun", "cut", "field", "sure", "rest", "watch", "correct", "color", "able", "face", "pound", "wood", "done", "main", "beauty", "enough", "drive", "plain", "stood", "girl", "contain", "usual", "front", "young", "teach", "ready", "week", "above", "final", "ever", "gave", "red", "green", "list", "oh", "though", "quick", "feel", "develop", "talk", "sleep", "bird", "warm", "soon", "free", "body", "minute", "dog", "strong", "family", "special", "direct", "mind", "pose", "behind", "leave", "clear", "song", "tail", "measure", "produce", "state", "fact", "product", "street", "black", "inch", "short", "lot", "numeral", "nothing", "class", "course", "wind", "stay", "question", "wheel", "happen", "full", "complete", "force", "ship", "blue", "area", "object", "half", "decide", "rock", "surface", "order", "deep", "fire", "moon", "south", "island", "problem", "foot", "piece", "yet", "told", "busy", "knew", "test", "pass", "record", "farm", "boat", "top", "common", "whole", "gold", "king", "possible", "size", "plane", "heard", "age", "best", "dry", "hour", "wonder", "better", "laugh", "true", "thousand", "during", "ago", "hundred", "ran", "am", "check", "remember", "game", "step", "shape", "early", "yes", "hold", "hot", "west", "miss", "ground", "brought", "interest", "heat", "reach", "snow", "fast", "bed", "five", "bring", "sing", "sit", "listen", "perhaps", "six", "fill", "table", "east", "travel", "weight", "less", "language", "morning", "among"];


window.$ = document.querySelectorAll.bind(document);


function shuffle(array) {
  let m = array.length,
      t,
      i;

  while (m) {
    
    i = Math.floor(Math.random() * m--); 

    t = array[m];
    array[m] = array[i];
    array[i] = t;
  }

  return array;
}


function addWords() {
  
  const wordSection = window.$("#word-section")[0];
  wordSection.innerHTML = "";
  window.$("#typebox")[0].value = "";

  for (let i = 350; i > 0; i--) {
    const words = shuffle(wordList);
    const wordSpan = `<span>${words[i]}</span>`;
    wordSection.innerHTML += wordSpan;
  }

  
  wordSection.firstChild.classList.add("current-word");
}


const colorCurrentWord = "#dddddd";
const colorCorrectWord = "#93C572";
const colorIncorrectWord = "#e50000";

const wordData = {
  seconds: 30,
  correct: 0,
  incorrect: 0,
  total: 0,
  typed: 0
};

function checkWord(word) {
  const wlen = word.value.length;
  const wval = word.value.trim();

  // How much we have of the current word.
  const current = window.$(".current-word")[0];
  const currentSubstring = current.innerHTML.substring(0, wlen);

  
  const noMatch = wval !== currentSubstring;
  const emptyWords = wval === '' || currentSubstring === '';

  if (noMatch || emptyWords) {
    current.classList.add("incorrect-word-bg");
    return false;
  } else {
    current.classList.remove("incorrect-word-bg");
    return true;
  }
}

function submitWord(word) {
 
  const current = window.$(".current-word")[0];

  if (checkWord(word)) {
    current.classList.remove("current-word");
    current.classList.add("correct-word-c");
    wordData.correct += 1;
  } else {
    current.classList.remove("current-word", "incorrect-word-bg");
    current.classList.add("incorrect-word-c");
    wordData.incorrect += 1;
  }

 
  wordData.total = wordData.correct + wordData.incorrect;

  
  current.nextSibling.classList.add("current-word");
}

function clearLine() {
  
  const wordSection = window.$("#word-section")[0];
  const current = window.$(".current-word")[0];
  const previous = current.previousSibling;
  const children = window.$(".correct-word-c, .incorrect-word-c").length;

  
  if (current.offsetTop > previous.offsetTop) {
    for (let i = 0; i < children; i++) {
      wordSection.removeChild(wordSection.firstChild);
    }
  }
}

let typingTimer = null;
function isTimer(seconds) {
 
  const time = window.$("#timer > span")[0].innerHTML;
  if (time === "0:00") {
    return false;
  }

  
  if (time === "0:30" && typingTimer === null) {
    typingTimer = window.setInterval(() => {
      if (seconds <= 0) {
        window.clearInterval(typingTimer);
      } else {
        seconds -= 1;
        const timePad = seconds < 10 ? "0" + seconds : seconds; 

        window.$("#timer > span")[0].innerHTML = `0:${timePad}`;
      }
    }, 1000);
  }

  return true;
}

function calculateWPM(data) {
  const { seconds, correct, incorrect, total, typed } = data;
  const minutes = seconds / 60;
  const wpm = Math.max(0, Math.ceil(((typed / 5) - incorrect) / minutes));
  const accuracy = Math.ceil((correct / total) * 100);

  const results = `
<ul id="results">
  <li>WPM: <span class="wpm-value">${wpm}</span></li>
  <li>Accuracy: <span class="wpm-value">${accuracy}%</span></li>
  <li id="results-stats">
    Total Words: <span>${total}</span> |
    Correct Words: <span>${correct}</span> |
    Incorrect Words: <span>${incorrect}</span> |
    Characters Typed: <span>${typed}</span>
  </li>
</ul>
`;

  window.$("#word-section")[0].innerHTML = results;


  const wpmClass = window.$("li:nth-child(2) .wpm-value")[0].classList;
  if (accuracy > 80) {
    wpmClass.add("correct-word-c");
  } else {
    wpmClass.add("incorrect-word-c");
  }

  console.log(wordData);
}

function typingTest(e) {
  const SPACE = 32;


  e = e || window.event;
  const kcode = e.keyCode;
  const word = window.$("#typebox")[0];

  
  if (word.value.match(/^\s/g)) {
    word.value = "";
    return;
  }

  
  const isGameover = !isTimer(wordData.seconds);
  if (isGameover) {
    calculateWPM(wordData);
    return;
  }

  
  checkWord(word);
  if (kcode === SPACE) {
    submitWord(word);
    clearLine();

    window.$("#typebox")[0].value = "";
  }

  wordData.typed += 1;
}

function restartTest() {
  window.$("#typebox")[0].value = "";
  window.location.reload();
}