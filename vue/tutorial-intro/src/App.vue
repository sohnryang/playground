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
  <button @click="reactiveCount++">Increment <code>reactiveCount</code>: {{ reactiveCount }}</button>
  <button @click="reactiveCount = 0">Reset <code>reactiveCount</code></button>
  <br>
  <button @click="nonReactiveCount++"> Increment <code>nonReactiveCount</code>: {{ nonReactiveCount }}</button>

  <h2>Computed Props</h2>
  <p>Challenge name: {{ challenge.name }}</p>
  <p>Is it a web challenge? {{ isWebChallenge }}</p>
</template>