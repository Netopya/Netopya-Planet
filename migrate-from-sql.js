const fs = require('fs');
const path = require('path');

// Function to clean HTML entities and fix encoding issues
function cleanContent(content) {
  return content
    .replace(/\\r\\n/g, '\n')
    .replace(/\\'/g, "'")
    .replace(/\\"/g, '"')
    .replace(/&frac12;/g, '½')
    .replace(/&frac14;/g, '¼')
    .replace(/&quot;/g, '"')
    .replace(/&#36;/g, '$')
    .replace(/&#8217;/g, "'")
    .replace(/&amp;/g, '&')
    .replace(/&lt;/g, '<')
    .replace(/&gt;/g, '>')
    .replace(/&nbsp;/g, ' ')
    .replace(/\t/g, '    ') // Convert tabs to 4 spaces
    .replace(/gallery_images\//g, '/gallery_images/')
    .replace(/article_images\//g, '/article_images/')
    .replace(/src="\/gallery_images\//g, 'src="/gallery_images/')
    .replace(/href="\/gallery_images\//g, 'href="/gallery_images/')
    .replace(/src="\/article_images\//g, 'src="/article_images/')
    .replace(/href="\/article_images\//g, 'href="/article_images/');
}

// Function to format dates
function formatDate(mysqlDate) {
  const date = new Date(mysqlDate);
  return date.toISOString().split('.')[0] + '.000Z';
}

// Function to map tags to categories
function getCategory(tag) {
  const tagMap = {
    'TUT': 'tutorials',
    'PROJ': 'projects', 
    'TOOL': 'tools'
  };
  return tagMap[tag] || 'uncategorized';
}

// Function to create filename from title and date
function createFilename(title, date) {
  const dateObj = new Date(date);
  const year = dateObj.getFullYear();
  const month = String(dateObj.getMonth() + 1).padStart(2, '0');
  const day = String(dateObj.getDate()).padStart(2, '0');
  
  const slug = title
    .toLowerCase()
    .replace(/[^\w\s-]/g, '')
    .replace(/\s+/g, '-')
    .replace(/-+/g, '-')
    .trim();
    
  return `${year}-${month}-${day}-${slug}.md`;
}

// Function to parse a single article record from CSV-like format
function parseArticleRecord(record) {
  const fields = [];
  let current = '';
  let inQuotes = false;
  let escapeNext = false;
  
  for (let i = 0; i < record.length; i++) {
    const char = record[i];
    
    if (escapeNext) {
      current += char;
      escapeNext = false;
      continue;
    }
    
    if (char === '\\') {
      current += char;
      escapeNext = true;
      continue;
    }
    
    if (char === "'") {
      inQuotes = !inQuotes;
      current += char;
      continue;
    }
    
    if (!inQuotes && char === ',') {
      fields.push(current.trim());
      current = '';
      continue;
    }
    
    current += char;
  }
  fields.push(current.trim()); // Add the last field
  
  return fields;
}

// Read the SQL file
const sqlContent = fs.readFileSync('old/netopyadb.sql', 'utf8');

console.log('Extracting all article data from SQL file...');

// Find all content between VALUES and the next CREATE TABLE or end of file
// Look for lines 47-63 specifically as mentioned by user
const lines = sqlContent.split('\n');
console.log(`Total lines in file: ${lines.length}`);

// Extract the specific range the user mentioned (lines 49-63)
const startLine = 48; // 0-indexed, so line 49 is index 48
const endLine = 62; // line 63 is index 62

console.log('Extracting lines 49-63 as requested...');
const relevantLines = lines.slice(startLine, endLine + 1);
const sqlData = relevantLines.join('\n');

console.log('Parsing VALUES data...');

// Find all article records - they start with ( and contain article data
const recordPattern = /\(\d+,\s*'[^']*'/g;
let match;
const allRecords = [];

// Extract all individual article records 
let recordStart = -1;
let parenDepth = 0;
let inQuotes = false;
let escapeNext = false;
let currentRecord = '';

for (let i = 0; i < sqlData.length; i++) {
  const char = sqlData[i];
  
  if (escapeNext) {
    currentRecord += char;
    escapeNext = false;
    continue;
  }
  
  if (char === '\\') {
    currentRecord += char;
    escapeNext = true;
    continue;
  }
  
  if (char === "'") {
    inQuotes = !inQuotes;
    currentRecord += char;
    continue;
  }
  
  if (!inQuotes) {
    if (char === '(') {
      if (parenDepth === 0) {
        // Start of a new record
        recordStart = i;
        currentRecord = '';
      }
      parenDepth++;
      currentRecord += char;
    } else if (char === ')') {
      parenDepth--;
      currentRecord += char;
      
      if (parenDepth === 0 && recordStart !== -1) {
        // End of record - remove outer parentheses and add to records
        const recordContent = currentRecord.slice(1, -1); // Remove ( )
        if (recordContent.trim()) {
          allRecords.push(recordContent);
        }
        currentRecord = '';
        recordStart = -1;
      }
    } else {
      currentRecord += char;
    }
  } else {
    currentRecord += char;
  }
}

console.log(`Found ${allRecords.length} article records`);

// Create posts directory if it doesn't exist
if (!fs.existsSync('src/posts')) {
  fs.mkdirSync('src/posts', { recursive: true });
}

// Parse each article record
allRecords.forEach((record, index) => {
  try {
    console.log(`Processing article ${index + 1}...`);
    
    const fields = parseArticleRecord(record);
    
    if (fields.length < 11) {
      console.warn(`Article ${index + 1} has only ${fields.length} fields, skipping`);
      return;
    }
    
    // Extract fields (remove surrounding quotes)
    const id = fields[0];
    const title = fields[1].replace(/^'|'$/g, '');
    const userId = fields[2];
    const timestamp = fields[3].replace(/^'|'$/g, '');
    const overfoldContent = fields[4].replace(/^'|'$/g, '');
    const content = fields[5].replace(/^'|'$/g, '');
    const ogImageUrl = fields[6].replace(/^'|'$/g, '');
    const description = fields[7].replace(/^'|'$/g, '');
    const galleryId = fields[8];
    const tag = fields[9].replace(/^'|'$/g, '');
    
    // Clean the content
    const cleanedOverfold = cleanContent(overfoldContent);
    const cleanedContent = cleanContent(content);
    const cleanedDescription = cleanContent(description);
    
    // Create the markdown content
    const filename = createFilename(title, timestamp);
    const category = getCategory(tag);
    const formattedDate = formatDate(timestamp);
    
    // Properly format the overfold content for YAML
    const formattedOverfold = cleanedOverfold
      .split('\n')
      .map(line => line ? '  ' + line : '')
      .join('\n');
    
    const markdown = `---
title: ${title}
date: ${formattedDate}
author: Netopya
category: ${category}
tag: ${tag}
layout: post
og_image: ${ogImageUrl}
description: ${cleanedDescription}
overfold_content: |
${formattedOverfold}
---

${cleanedContent}`;

    // Write the file
    const filepath = path.join('src/posts', filename);
    fs.writeFileSync(filepath, markdown);
    console.log(`✓ Created ${filename} - ${title}`);
    
  } catch (error) {
    console.error(`Error processing article ${index + 1}:`, error.message);
  }
});

console.log('\nMigration complete! All articles have been generated from the SQL database.'); 