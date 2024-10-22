document.addEventListener("DOMContentLoaded", function () {
  console.log("JavaScript is loaded");
  const form = document.querySelector("form");
  form.addEventListener("submit", function (event) {
    alert("Form is submitted");
  });
});
