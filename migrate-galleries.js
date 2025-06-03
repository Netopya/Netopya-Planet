const fs = require('fs');
const path = require('path');

// Read the SQL file
const sqlContent = fs.readFileSync('old/netopyadb.sql', 'utf8');

console.log('Extracting gallery images from SQL file...');

// Extract the gallery_images INSERT section
const lines = sqlContent.split('\n');
const insertLine = lines.findIndex(line => line.includes('INSERT INTO `gallery_images`'));

if (insertLine === -1) {
  console.error('Could not find gallery_images INSERT statement');
  process.exit(1);
}

// Find all gallery image records starting from the INSERT line
let galleryData = '';
let foundStart = false;
let parenDepth = 0;

for (let i = insertLine; i < lines.length; i++) {
  const line = lines[i];
  
  if (line.includes('INSERT INTO `gallery_images`')) {
    foundStart = true;
    // Extract just the VALUES part
    const valuesIndex = line.indexOf('VALUES');
    if (valuesIndex !== -1) {
      galleryData += line.substring(valuesIndex + 6).trim();
    }
    continue;
  }
  
  if (foundStart) {
    // Stop when we hit the next table or end
    if (line.includes('-- --------------------------------------------------------') || 
        line.includes('CREATE TABLE') || 
        line.includes('-- Indexes')) {
      break;
    }
    galleryData += '\n' + line;
  }
}

console.log('Parsing gallery image records...');

// Parse gallery records similar to article parsing
const allRecords = [];
let recordStart = -1;
parenDepth = 0;
let inQuotes = false;
let escapeNext = false;
let currentRecord = '';

for (let i = 0; i < galleryData.length; i++) {
  const char = galleryData[i];
  
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

console.log(`Found ${allRecords.length} gallery image records`);

// Function to parse a gallery record
function parseGalleryRecord(record) {
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

// Group images by gallery_id
const galleries = {};

allRecords.forEach((record, index) => {
  try {
    const fields = parseGalleryRecord(record);
    
    if (fields.length < 7) {
      console.warn(`Gallery image ${index + 1} has only ${fields.length} fields, skipping`);
      return;
    }
    
    const id = parseInt(fields[0]);
    const galleryId = parseInt(fields[1]);
    const name = fields[2].replace(/^'|'$/g, '');
    const description = fields[3].replace(/^'|'$/g, '').replace(/\\'/g, "'").replace(/\\"/g, '"');
    const thbUrl = fields[4].replace(/^'|'$/g, '');
    const lrgUrl = fields[5].replace(/^'|'$/g, '');
    const fullUrl = fields[6].replace(/^'|'$/g, '');
    
    // Convert paths to absolute paths
    const cleanThbUrl = '/' + thbUrl;
    const cleanLrgUrl = '/' + lrgUrl;
    const cleanFullUrl = '/' + fullUrl;
    
    if (!galleries[galleryId]) {
      galleries[galleryId] = [];
    }
    
    galleries[galleryId].push({
      id,
      name,
      description,
      thumbnail: cleanThbUrl,
      large: cleanLrgUrl,
      full: cleanFullUrl
    });
    
  } catch (error) {
    console.error(`Error processing gallery image ${index + 1}:`, error.message);
  }
});

// Create data directory for galleries
const dataDir = 'src/_data';
if (!fs.existsSync(dataDir)) {
  fs.mkdirSync(dataDir, { recursive: true });
}

// Write gallery data files
Object.keys(galleries).forEach(galleryId => {
  const galleryImages = galleries[galleryId];
  const filename = path.join(dataDir, `gallery_${galleryId}.json`);
  
  fs.writeFileSync(filename, JSON.stringify(galleryImages, null, 2));
  console.log(`✓ Created ${filename} with ${galleryImages.length} images`);
});

// Create a master galleries index
const allGalleries = Object.keys(galleries).map(id => ({
  id: parseInt(id),
  count: galleries[id].length,
  images: galleries[id]
}));

fs.writeFileSync(path.join(dataDir, 'galleries.json'), JSON.stringify(allGalleries, null, 2));
console.log(`✓ Created galleries.json with ${allGalleries.length} galleries`);

console.log('\nGallery migration complete!'); 