const fs = require('fs');
const path = require('path');

// Read the SQL file
const sqlContent = fs.readFileSync('old/netopyadb.sql', 'utf8');

console.log('Extracting articles from SQL file...');

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

// Extract the section containing the INSERT statements for articles
const lines = sqlContent.split('\n');
const startLines = [];

// Find both INSERT statements for articles 
for (let i = 0; i < lines.length; i++) {
  if (lines[i].includes('INSERT INTO `articles`')) {
    startLines.push(i);
  }
}

if (startLines.length === 0) {
  console.error('Could not find articles INSERT statements');
  process.exit(1);
}

console.log(`Found ${startLines.length} INSERT statements`);

// Extract content from lines 49-63 (inclusive, 1-indexed)
const startLine = 48; // 0-indexed
const endLine = 62;   // 0-indexed, inclusive

let articlesData = '';
for (let i = startLine; i <= endLine; i++) {
  if (i < lines.length) {
    articlesData += lines[i] + '\n';
  }
}

console.log('Parsing article records...');

// Find and extract all records
const allRecords = [];
let recordStart = -1;
let parenDepth = 0;
let inQuotes = false;
let escapeNext = false;
let currentRecord = '';

for (let i = 0; i < articlesData.length; i++) {
  const char = articlesData[i];
  
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

// Function to parse a record
function parseRecord(record) {
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
  fields.push(current.trim());
  return fields;
}

// Function to create filename from title and timestamp
function createFilename(title, timestamp) {
  const date = new Date(timestamp);
  const year = date.getFullYear();
  const month = String(date.getMonth() + 1).padStart(2, '0');
  const day = String(date.getDate()).padStart(2, '0');
  
  const slug = title
    .toLowerCase()
    .replace(/[^a-z0-9\s-]/g, '')
    .replace(/\s+/g, '-')
    .replace(/-+/g, '-')
    .trim();
  
  return `${year}-${month}-${day}-${slug}.md`;
}

// Function to get category from tag
function getCategory(tag) {
  const tagMap = {
    'TUT': 'tutorials',
    'PROJ': 'projects', 
    'TOOL': 'tools'
  };
  return tagMap[tag] || 'posts';
}

// Function to format date
function formatDate(timestamp) {
  return new Date(timestamp).toISOString();
}

// Create posts directory
const postsDir = 'src/posts';
if (!fs.existsSync(postsDir)) {
  fs.mkdirSync(postsDir, { recursive: true });
}

let successCount = 0;

// Process each record
allRecords.forEach((record, index) => {
  try {
    const fields = parseRecord(record);
    
    if (fields.length < 11) {
      console.warn(`Article ${index + 1} has only ${fields.length} fields, skipping`);
      return;
    }
    
    const id = parseInt(fields[0]);
    const title = fields[1].replace(/^'|'$/g, '');
    const userId = parseInt(fields[2]);
    const timestamp = fields[3].replace(/^'|'$/g, '');
    const overfoldContent = fields[4].replace(/^'|'$/g, '');
    const content = fields[5].replace(/^'|'$/g, '');
    const ogImageUrl = fields[6].replace(/^'|'$/g, '');
    const description = fields[7].replace(/^'|'$/g, '');
    const galleryId = parseInt(fields[8]) || 0; // Extract gallery_id
    const tag = fields[9].replace(/^'|'$/g, '');
    const featureClip = fields[10].replace(/^'|'$/g, '');
    
    // Clean the content
    const cleanedContent = cleanContent(content);
    const cleanedOverfold = cleanContent(overfoldContent);
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
description: ${cleanedDescription}${galleryId > 0 ? `\ngallery_id: ${galleryId}` : ''}
overfold_content: |
${formattedOverfold}
---

${cleanedContent}`;
    
    // Write the file
    const filepath = path.join(postsDir, filename);
    fs.writeFileSync(filepath, markdown);
    
    console.log(`✓ Created ${filename} (Gallery ID: ${galleryId || 'none'})`);
    successCount++;
    
  } catch (error) {
    console.error(`Error processing article ${index + 1}:`, error.message);
  }
});

console.log(`\nMigration complete! Created ${successCount} articles.`); 