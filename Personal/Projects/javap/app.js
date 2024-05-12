const puppeteer = require("puppeteer");
const fs = require('fs');

(async () => {
  const browser = await puppeteer.launch({ headless: "new" });
  const page = await browser.newPage();
  const currentDate = new Date();
  console.log('Current date:', currentDate);

  await page.setViewport({ width: 1200, height: 800 }); // Change the width and height as needed
  await page.goto("https://www.microcenter.com/product/668520/asus-nvidia-geforce-rtx-4090-rog-strix-lc-overclocked-liquid-cooled-24gb-gddr6x-pcie-40-graphics-card");
  
  // Replace 'className' with the actual class name of the element containing the text
  const textSelector = "p.big-price"; // Example selector targeting a <p> element with a class 'some-class'
  
  // Get the text content of the element with the specified class name using page.evaluate
  const selectedText = await page.evaluate((selector) => {
    const textElement = document.querySelector(selector);
    return textElement ? textElement.textContent : null;
  }, textSelector);

  console.log("Selected text:", selectedText);
  // await page.screenshot({ path: "puppeteer.png" });

  await browser.close();

  // Updating the file
  // Specify the file path
  const filePath = 'rtx4090prices.txt';

  // Write content to the file
  fs.appendFile(filePath, currentDate + ' ' + selectedText.trim() + "\n", err => {
    if (err) {
      console.error('Error writing to file:', err);
      return;
    }
    console.log('Content has been written to the file.');
  });
})();

