<script setup lang="ts">
import { computed, reactive, ref } from 'vue';

function showDialog() {
  alert(1)
}

function increment() {
  count.value++;
}

const count = ref<number>(0)
const message = "Hell world!"

let nonReactiveCount = 0
const reactiveCount = ref<number>(0);

const challenge = reactive({
  name: "JLVM",
  tags: ["web", "prototype-pollution", "local-file-inclusion"],
})

const isWebChallenge = computed(() => {
  return challenge.tags.includes("web") ? "Yes" : "No"
})

const isTextEnabled = ref<Boolean>(true);

const enableToggleButtonText = computed(() => {
  return isTextEnabled.value ? "Disable" : "Enable"
})

const fontSize = ref(10)

const challenges = ["JLVM", "Stylish Memo", "Big Fan"]
const messages = ref([
  { title: "Hello", content: "world" },
  { title: "Goodbye", content: "hell" },
  { title: "What", content: "is happening?" },
])

const censoredMessages = computed(() => {
  return messages.value.filter((m) => !m.content.includes("hell"))
})

function greet() {
  alert("Hi!")
}

function say(message: string) {
  alert(`Said: ${message}`)
}

const eventButtonText = ref<string>("Not clicked")
</script>

<template>
  <h1>{{ message }}</h1>
  <h2>Template Tutorial</h2>
  <button @click="showDialog">Click me!</button>
  <br>
  <button @click="increment">Count: {{ count }}</button>
  <br>
  <span v-if="count % 2 == 0">The <code>count</code> is even!</span>
  <br>
  <span v-if="count % 2 == 1">The <code>count</code> is odd!</span>

  <h2>Reactivity</h2>
  <button @click="reactiveCount++">
    Increment <code>reactiveCount</code>: {{ reactiveCount }}
  </button>
  <button @click="reactiveCount = 0">
    Reset <code>reactiveCount</code>
  </button>
  <br>
  <button @click="nonReactiveCount++">
    Increment <code>nonReactiveCount</code>: {{ nonReactiveCount }}
  </button>

  <h2>Computed Props</h2>
  <p>Challenge name: {{ challenge.name }}</p>
  <p>Is it a web challenge? {{ isWebChallenge }}</p>

  <h2>Class and Style Bindings</h2>
  <p :class="{ 'disabled-text': !isTextEnabled }">Some text</p>
  <button @click="isTextEnabled = !isTextEnabled">
    {{ enableToggleButtonText }}
  </button>
  <p :style="{ 'font-size': fontSize + 'px' }">
    Resizable text (size: {{ fontSize }}px)
  </p>
  <button @click="fontSize += 10">Increase <code>fontSize</code></button>
  <button @click="fontSize -= 10">Decrease <code>fontSize</code></button>

  <h2>List Rendering</h2>
  <p>List of CTF challenges</p>
  <ol>
    <li v-for="chall of challenges">
      {{ chall }}
    </li>
  </ol>

  <li v-for="({ title, content }, index) of messages">
    Index {{ index }} -- {{ title }}: {{ content }}
  </li>

  <p>Counting to 10:</p>
  <div v-for="n in 10">{{ n }}</div>

  <p>Censored messages</p>
  <li v-for="({ title, content }, index) of censoredMessages">
    Index {{ index }} -- {{ title }}: {{ content }}
  </li>

  <h2>Event Handling</h2>
  <button @click="greet">Greet</button>
  <button @click="say('hi')">Say "hi"</button>
  <input type="text" @keypress.enter="greet">
  <textarea cols="30" rows="10" @keypress.enter.prevent="greet"></textarea>
</template>

<style scoped>
.disabled-text {
  color: lightgray;
}
</style>